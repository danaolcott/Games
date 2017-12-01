///////////////////////////////////////////////////////
/*
Dana Olcott 2017

Touch Panel Controller Files for the touch screen
component to the lcd on the stm32f429 discovery
board.

Touch screen uses the the STM811 controller ic
and is wired up to the I2C3 peripheral.

hi2c3

 I2C3 GPIO Configuration
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL

For now, make somethinng simple to read the product code

Next, 
enable the interrupt pin (EXTI line 15)
read the x and y position from the touch panel

API function calls:

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);


location data:
x and y are 12 bits, no need for z data
default x is increasing to the left (need to reverse)
default y is increasing down (ok)

normalize x and y read values to LCD_WIDTH and LCD_HEIGHT

*/
//////////////////////////////////////////////////////////

#include "TouchPanel.h"
#include "i2c.h"
#include "gpio.h"

#include "Graphics.h"

///////////////////////////////////////////////
//variables
static TouchPanelData m_touchPanelData;

////////////////////////////////////////
//reads the chip id and id version.
//returns... 0 if ok, -1 if not
//
void TouchPanel_init(void)
{
	m_touchPanelData.xPos = 0x00;
	m_touchPanelData.yPos = 0x00;
	m_touchPanelData.xRawPos = 0x00;
	m_touchPanelData.yRawPos = 0x00;

	//uint16_t chipID = TouchPanel_readChipID();
	//uint8_t IDVersion = TouchPanel_readIDVersion();

	TouchPanel_writeReg1Byte(TP_REG_SYS_CTRL1, 0x02);		//reset, bit 1, no hibernate

	//disable the clock gating
	TouchPanel_writeReg1Byte(TP_REG_SYS_CTRL2, 0x0F);		//switch off ts, gpio, tsc, adc

	//configure the controller - read only x and y data
	//no window tracking
	//write 00000010 - x and y only, no tracking, EN bit low = 0x02
	//write 00000011 - x and y only, no tracking, EN bit high = 0x03

	TouchPanel_writeReg1Byte(TP_REG_TSC_CTRL, 0x00);		//no window tracking, xy data, EN bit low
	TouchPanel_writeReg1Byte(TP_REG_TSC_CTRL, 0x02);		//no window tracking, xy data, EN bit low

	//tsc_config
	//1 sample 00, det delay 50us 001, settling 100us 001, 00001001
//	TouchPanel_writeReg1Byte(TP_REG_TSC_CFG, 0x09);

	//2 samples 01, det delay 50us 001, settling 100us 001, 01001001
//	TouchPanel_writeReg1Byte(TP_REG_TSC_CFG, 0x49);

	//increase the delay and settling time....
	//
	//2 samples 01, det delay 1ms = 100  , settling 1ms = 011....  01100011
	TouchPanel_writeReg1Byte(TP_REG_TSC_CFG, 0x63);

	//configure the fifo - fifo 2, two elements in the fifo to trigger
	TouchPanel_writeReg1Byte(TP_REG_TSC_FIFO_TH, 0x02);

	//configure the interrupts
	//int control - falling edge, edge interrupt, global 0x03
	TouchPanel_writeReg1Byte(TP_REG_INT_CTRL, 0x03);

	//enable touch detect interrupt
	TouchPanel_writeReg1Byte(TP_REG_INT_EN, 0x01);

	//reset the fifo
	TouchPanel_writeReg1Byte(TP_REG_TSC_FIFO_STA, 0x21);
	TouchPanel_writeReg1Byte(TP_REG_TSC_FIFO_STA, 0x20);

	//enable the clocks - all clocks on
	TouchPanel_writeReg1Byte(TP_REG_SYS_CTRL2, 0x00);

	//set the EN bit to enable the panel and start detecting
	TouchPanel_writeReg1Byte(TP_REG_TSC_CTRL, 0x03);
}

uint8_t TouchPanel_readReg1Byte(uint16_t reg)
{
	uint8_t value = 0x00;
	HAL_I2C_Mem_Read(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, &value, 1, 0xFF);

	return value;
}

///////////////////////////////////////////////
//hal i2c read
//reads into msb followed by lsb
//
uint16_t TouchPanel_readReg2Bytes(uint16_t reg)
{
	uint8_t value[2] = {0x00, 0x00};
	HAL_I2C_Mem_Read(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, value, 2, 0xFF);

	//reads into msb then lsb
	uint16_t result = ((uint16_t)value[0]) << 8;
	result |= value[1];

	return result;
}

uint32_t TouchPanel_readReg4Bytes(uint16_t reg)
{
	uint8_t value[4] = {0x00, 0x00, 0x00, 0x00};
	HAL_I2C_Mem_Read(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, value, 4, 0xFF);

	//reads into most to least
	uint32_t result = ((uint32_t)value[0]) << 24;
	result |= ((uint32_t)value[1]) << 16;
	result |= ((uint32_t)value[2]) << 8;
	result |= ((uint32_t)value[3]);

	return result;
}


///////////////////////////////////////////
//top 8 bits are don't care
uint32_t TouchPanel_readReg3Bytes(uint16_t reg)
{
	uint8_t value[3] = {0x00, 0x00, 0x00};
	HAL_I2C_Mem_Read(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, value, 3, 0xFF);

	//reads into most to least
	uint32_t result = ((uint32_t)value[0]) << 16;
	result |= ((uint32_t)value[1]) << 8;
	result |= ((uint32_t)value[2]);

	return result;
}


void TouchPanel_writeReg1Byte(uint16_t reg, uint8_t value)
{
	uint8_t data = value;
	HAL_I2C_Mem_Write(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, &data, 1, 0xFF);
}

////////////////////////////////////////////////
//write 2 bytes - write most followed by least
void TouchPanel_writeReg2Bytes(uint16_t reg, uint16_t value)
{
	uint8_t data[2] = {0x00, 0x00};
	data[0] = (value >> 8) & 0xFF;
	data[1] = value & 0xFF;

	HAL_I2C_Mem_Write(&hi2c3, TOUCH_PANEL_ADDRESS, reg, 1, data, 2, 0xFF);
}


///////////////////////////////////////
//read 2 byte value - chip id register
uint16_t TouchPanel_readChipID()
{
	uint16_t ret = TouchPanel_readReg2Bytes(TOUCH_PANEL_CHIP_ID_REG);
	return ret;
}
uint8_t TouchPanel_readIDVersion()
{
	uint8_t ret = TouchPanel_readReg1Byte(TOUCH_PANEL_ID_VER_REG);
	return ret;
}
uint8_t TouchPanel_GetFIFOStatus(void)
{
	uint8_t status = TouchPanel_readReg1Byte(TP_REG_TSC_FIFO_STA);
	return status;
}
uint8_t TouchPanel_GetFIFOSize(void)
{
	uint8_t level = TouchPanel_readReg1Byte(TP_REG_TSC_FIFO_SIZE);
	return level;
}

////////////////////////////////////////
//FIFO_STA - bit 5 high if empty
//returns 1 if empty
uint8_t TouchPanel_FIFO_isEmpty(void)
{
	uint8_t status = TouchPanel_readReg1Byte(TP_REG_TSC_FIFO_STA);
	return ((status >> 5) & 0x01);
}


/////////////////////////////////
//clears the contents in the fifo

void TouchPanel_FIFO_clear(void)
{
	TouchPanel_writeReg1Byte(TP_REG_TSC_FIFO_STA, 0x01);
}
///////////////////////////////////////////////
//Read xyz data and fifo level
//if nothing in the fifo, returns all zeros
//uses the compact xyz register for reading data
//try reading the clunky way first...
//
//should probably change this to int return,
//where 0 is ok, -1 is no data...

//reads the raw data, normalizes with respect
//to panel width and height
//
TouchPanelData TouchPanel_readRawData(void)
{
	TouchPanelData data;
	uint8_t size = 0x00;
	uint32_t temp, tempX, tempY;

	data.xPos = 0x00;
	data.yPos = 0x00;

	//data sets remaining in the fifo
	size = TouchPanel_readReg1Byte(TP_REG_TSC_FIFO_SIZE);

	//read position data if there's something to read
	if (size > 0)
	{
		//read 3 bytes - x and y data only
		//top 8 bits are don't care
		temp = TouchPanel_readReg3Bytes(TP_REG_TSC_DATA_XYZ);

		tempX = ((temp >> 12) & 0xFFF);
		tempY = temp & 0xFFF;

		//invert x to make icnreasing to the right
		tempX = 4095 - tempX;

		data.xRawPos = tempX;
		data.yRawPos = tempY;

		//normalize to the width/heigth, accounting for the min and max
		if (tempX < TOUCH_PANEL_CALIB_X_MIN)
			tempX = 0;
		else if (tempX > TOUCH_PANEL_CALIB_X_MAX)
			tempX = TOUCH_PANEL_WIDTH;
		else
			tempX = (tempX - TOUCH_PANEL_CALIB_X_MIN) * TOUCH_PANEL_WIDTH / (TOUCH_PANEL_CALIB_X_MAX - TOUCH_PANEL_CALIB_X_MIN);

		if (tempY < TOUCH_PANEL_CALIB_Y_MIN)
			tempY = 0;
		else if (tempY > TOUCH_PANEL_CALIB_Y_MAX)
			tempY = TOUCH_PANEL_HEIGHT;
		else
			tempY = (tempY - TOUCH_PANEL_CALIB_Y_MIN) * TOUCH_PANEL_HEIGHT / (TOUCH_PANEL_CALIB_Y_MAX - TOUCH_PANEL_CALIB_Y_MIN);

		data.xPos = (uint16_t)tempX;
		data.yPos = (uint16_t)tempY;
	}

	return data;
}


////////////////////////////////////////
//return the current touch location on the panel.
//m_touchPanelData is updated in the isr, gpio exti
//line interrupt.
//
TouchPanelData TouchPanel_getPosition(void)
{
	return m_touchPanelData;
}

void TouchPanel_setPosition(TouchPanelData data)
{
	m_touchPanelData.xPos = data.xPos;
	m_touchPanelData.yPos = data.yPos;
	m_touchPanelData.xRawPos = data.xRawPos;
	m_touchPanelData.yRawPos = data.yRawPos;
}

///////////////////////////////////////
//touch detected
//TSC_CTRL reg - bit 7 high if detected
//
uint8_t TouchPanel_touchDetected(void)
{
	uint8_t result = TouchPanel_readReg1Byte(TP_REG_TSC_CTRL);
	return ((result >> 7) & 0x01);
}


/////////////////////////////////////////
//reads the interrupt status register for
//which interrupts have been triggered
//return only the touch detected, or bit 0
uint8_t TouchPanel_interruptStatus(void)
{
	uint8_t status = TouchPanel_readReg1Byte(TP_REG_INT_STA);
	return (status & 0x01);
}

//////////////////////////////////////////
//clears touch detected interrupt
void TouchPanel_interruptClear(void)
{
	TouchPanel_writeReg1Byte(TP_REG_INT_STA, 0x01);
}


///////////////////////////////////////////////////
//Interrupt Callback from the TouchPanel
//Triggers when the panel is touched.
//There must be a flag you have to clear
//in the panel registers because it only triggers
//first time then no further detection
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	volatile TouchPanelData data;
	volatile uint8_t size;

	if (GPIO_Pin == Touch_Panel_EXTI15_Pin)
	{
		size = TouchPanel_GetFIFOSize();

		//read data size times
		for (int i = 0 ; i < size ; i++)
		{
			data = TouchPanel_readRawData();
			TouchPanel_setPosition(data);		//update position
		}

	}

	TouchPanel_interruptClear();		//clear the interrupt
}


