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
 *  1 - A0
 *  2 - A1
 *  3 - A2
 *  4 - Vss - GND
 *  5 - SDA - PB9 - 2k pullups
 *  6 - SCL - PB8 - 2k pullups
 *  7 - WP - PC9 - NOTE: Tie this to ground!!  no need for extra pin
 *  8 - Vcc - 3.3V
 *
 */

#ifndef GAME_EEPROM_H_
#define GAME_EEPROM_H_

#define EEPROM_TEST_ADDR		0x50


void EEPROM_init(void);
void EEPROM_writeByte(uint16_t address, uint8_t data);
uint8_t EEPROM_readByte(uint16_t address);

void EEPROM_writeMultiByte(uint16_t address, uint8_t* data, uint8_t len);
void EEPROM_readMultiByte(uint16_t address, uint8_t* data, uint8_t len);




#endif /* GAME_EEPROM_H_ */




