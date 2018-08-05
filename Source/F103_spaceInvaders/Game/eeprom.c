/*
 * eeprom.h
 *
 *  Created on: Jul 22, 2018
 *      Author: danao
 *
 *  EEPROM Control Write/Read
 *  Microchip
 *  PN: 24LC01B-I/P
 *
 *  I2C memory chip used for storing high score and other game
 *  settings.  The IC had address 0xA0 and located on I2C1
 *  on pins PB8 and PB9.
 *
 *  From datasheet, Pinout:
 *  1 - A0 - NC
 *  2 - A1 - NC
 *  3 - A2 - NC
 *  4 - Vss - GND
 *  5 - SDA - PB9 - 2k pullups
 *  6 - SCL - PB8 - 2k pullups
 *  7 - WP - GND
 *  8 - Vcc - 3.3V
 *
 *  Notes About I2C on the STM32F103 Nucleo Board
 *
 *  I2C on the arduiono headers is i2c1 remapped value.
 *  To use this, small modication to the i2c auto gen
 *  code is required: put the remap io af function before
 *  the initialiation call.
 *
 *  To use the SPI with I2C, the chip select that is typically
 *  used on the arduino board (shields) is D10.  This is the
 *  the same pin as I2C SCL - NON-remapped value.  You cant
 *  use this as the CS pin if you're using I2C as well.  Fix is
 *  to simply use a different pin for chip select and make a
 *  small modification to the shield.
 *
 *
 *
 */


#include "gpio.h"
#include "i2c.h"
#include "eeprom.h"


/////////////////////////////////////////////
//EEPROM_DummyDelay(uint32_t)
static void EEPROM_DummyDelay(uint32_t delay)
{
	volatile uint32_t value = delay;

	while (value > 0)
		value--;

}

////////////////////////////////////////
//EEPROM IC uses I2C1
//Write a byte to test address and read it
//back.
void EEPROM_init(void)
{
	uint8_t data = 0xAA;
	EEPROM_writeByte(EEPROM_TEST_ADDR, data);
	uint8_t result = EEPROM_readByte(EEPROM_TEST_ADDR);

	if (data != result)
	{
		while(1){};
	}
}



//////////////////////////////////////////////////////
//Write 1 data byte to address on i2c peripheral.
//Number of address bytes is 1.  See Figure 6-1 in datasheet
//
void EEPROM_writeByte(uint16_t address, uint8_t data)
{
	uint8_t tx = data;
	HAL_I2C_Mem_Write(&hi2c1, 0xA0, address, 1, &tx, 1, 0xFFFF);
	EEPROM_DummyDelay(200000);

}

/////////////////////////////////////////////////////////
//Read 1 byte from address.
//
uint8_t EEPROM_readByte(uint16_t address)
{
	uint8_t rx = 0x00;
	HAL_I2C_Mem_Read(&hi2c1, 0xA0, address, 1, &rx, 1, 0xFFFF);
	EEPROM_DummyDelay(200000);
	return rx;
}



///////////////////////////////////////////////////
//Write array of data start at address address, len bytes
void EEPROM_writeMultiByte(uint16_t address, uint8_t* data, uint8_t len)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xA0, address, 1, data, len, 0xFFFF);
	EEPROM_DummyDelay(200000);
}


/////////////////////////////////////////////////////
//Read len bytes into data array, starting at address
void EEPROM_readMultiByte(uint16_t address, uint8_t* data, uint8_t len)
{
	HAL_I2C_Mem_Read(&hi2c1, 0xA0, address, 1, data, len, 0xFFFF);
	EEPROM_DummyDelay(200000);
}







