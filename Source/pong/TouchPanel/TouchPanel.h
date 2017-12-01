///////////////////////////////////////////////////////
/*
Dana Olcott 2017

Touch Panel Controller Files for the touch screen
component to the lcd on the stm32f429 discovery
board.

Touch screen uses the the STM811 controller ic
and is wired up to the I2C3 peripheral.


For now, make somethinng simple to read the product code

Next, 
enable the interrupt pin (EXTI line 15)
read the x and y position from the touch panel


*/
//////////////////////////////////////////////////////////

#ifndef __TOUCH_PANEL_H
#define __TOUCH_PANEL_H

#include "i2c.h"


#define TOUCH_PANEL_WIDTH		240
#define TOUCH_PANEL_HEIGHT		320

//normalize to a range
#define TOUCH_PANEL_CALIB_X_MIN		((uint32_t)500)
#define TOUCH_PANEL_CALIB_X_MAX		((uint32_t)3600)
#define TOUCH_PANEL_CALIB_Y_MIN		((uint32_t)500)
#define TOUCH_PANEL_CALIB_Y_MAX		((uint32_t)3600)

//address
#define TOUCH_PANEL_ADDRESS		0x82

#define TOUCH_PANEL_CHIP_ID		((uint16_t)0x0811)
#define TOUCH_PANEL_ID_VER		((uint8_t)0x03)

//register defines
#define TOUCH_PANEL_CHIP_ID_REG		0x00		//2 bytes 0x0811
#define TOUCH_PANEL_ID_VER_REG		0x02		//1 byte 0x03

#define TP_REG_SYS_CTRL1			0x03		//1 byte - reset control
#define TP_REG_SYS_CTRL2			0x04		//1 byte - clock gating and touch screen controller

#define TP_REG_SPI_CFG				0x08		//1 byte - SPI auto increment bit 2

#define TP_REG_INT_CTRL				0x09		//1 byte - interrupt control
#define TP_REG_INT_EN				0x0A		//1 byte - interrupt enable
#define TP_REG_INT_STA				0x0B		//1 byte - interrupt status

#define TP_REG_TSC_CTRL				0x40		//touch screen control reg - EN bit
#define TP_REG_TSC_CFG				0x41		//1 byte - panel voltage settling time
#define TP_REG_TSC_FIFO_TH			0x4A		//1 byte - fifo threshold to cause interrupt
#define TP_REG_TSC_FIFO_STA			0x4B		//1 byte - fifo status register
#define TP_REG_TSC_FIFO_SIZE		0x4C		//1 byte - current fifo size - read till below the threshold

//data reg
#define TP_REG_TSC_DATA_X			0x4D		//x data - 2 bytes
#define TP_REG_TSC_DATA_Y			0x4F		//y data - 2 bytes
#define TP_REG_TSC_DATA_Z			0x51		//z data - 1 byte
#define TP_REG_TSC_DATA_XYZ			0x52		//xyz data - 4 bytes

typedef struct
{
	uint16_t xPos;
	uint16_t yPos;
	uint16_t xRawPos;
	uint16_t yRawPos;

}TouchPanelData;



void TouchPanel_init(void);
uint8_t TouchPanel_readReg1Byte(uint16_t reg);
uint16_t TouchPanel_readReg2Bytes(uint16_t reg);
uint32_t TouchPanel_readReg3Bytes(uint16_t reg);
uint32_t TouchPanel_readReg4Bytes(uint16_t reg);

void TouchPanel_writeReg1Byte(uint16_t reg, uint8_t value);
void TouchPanel_writeReg2Bytes(uint16_t reg, uint16_t value);

uint16_t TouchPanel_readChipID(void);
uint8_t TouchPanel_readIDVersion(void);

uint8_t TouchPanel_GetFIFOStatus(void);
uint8_t TouchPanel_GetFIFOSize(void);
uint8_t TouchPanel_FIFO_isEmpty(void);
void TouchPanel_FIFO_clear(void);

TouchPanelData  TouchPanel_readRawData(void);
TouchPanelData TouchPanel_getPosition(void);
void TouchPanel_setPosition(TouchPanelData data);

uint8_t TouchPanel_touchDetected(void);
uint8_t TouchPanel_interruptStatus(void);
void TouchPanel_interruptClear(void);


#endif
