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
 *  on pins PB8 and PB9.  Also uses the following control lines:
 *
 *  PC9 - WP - Write Protect Pin
 *
 *  From datasheet, Pinout:
 *  1 - A0 - NC
 *  2 - A1 - NC
 *  3 - A2 - NC
 *  4 - Vss - GND
 *  5 - SDA - PB9 - 2k pullups
 *  6 - SCL - PB8 - 2k pullups
 *  7 - WP - PC9 - Should just tie this to ground all the time
 *  8 - Vcc - 3.3V
 *
 */


#include "gpio.h"
#include "i2c.h"
#include "eeprom.h"


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
	HAL_I2C_Mem_Write(&hi2c1, 0xA0, address, 1, &tx, 1, 0xFF);
}

/////////////////////////////////////////////////////////
//Read 1 byte from address.
//
uint8_t EEPROM_readByte(uint16_t address)
{
	uint8_t rx = 0x00;
	HAL_I2C_Mem_Read(&hi2c1, 0xA0, address, 1, &rx, 1, 0xFF);

	return rx;
}



///////////////////////////////////////////////////
//Write array of data start at address address, len bytes
void EEPROM_writeMultiByte(uint16_t address, uint8_t* data, uint8_t len)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xA0, address, 1, data, len, 0xFF);
}


/////////////////////////////////////////////////////
//Read len bytes into data array, starting at address
void EEPROM_readMultiByte(uint16_t address, uint8_t* data, uint8_t len)
{
	HAL_I2C_Mem_Read(&hi2c1, 0xA0, address, 1, data, len, 0xFF);
}







