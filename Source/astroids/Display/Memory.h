/*
Memory Driver / Control functions for SDRAM

Many of the functions taken from the st libs bsp for sdram


*/

#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "fmc.h"
#include "dma.h"

#include "Graphics.h"

#define SDRAM_DEVICE_SIZE         ((uint32_t)0x800000)  /* SDRAM device size in MBytes */

#define SDRAM_BASE_ADDR				((uint32_t)0xD0000000)

//we can do 0x800, but wanted to make the numbers line up.
#define SDRAM_READ_WRITE_OFFSET		((uint32_t)0x1000)		//4096 bytes
#define SDRAM_PAGE_SIZE				((uint32_t)0x1000)		//4096 bytes

#define SDRAM_LCD_LAYER_OFFSET		((uint32_t)0x20000)		//0xD0020000, 0xD0040000, ...
#define SDRAM_LCD_LAYER_SIZE		((uint32_t)0x20000)		//0xD0020000, 0xD0040000, ...

//deref value

//#define SDRAM_LCD_LAYER_0			(*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET))
//#define SDRAM_LCD_LAYER_1			(*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + SDRAM_LCD_LAYER_SIZE))

//address
#define SDRAM_LCD_LAYER_0			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET)
#define SDRAM_LCD_LAYER_1			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + SDRAM_LCD_LAYER_SIZE)
#define SDRAM_LCD_LAYER_2			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (2*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_3			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (3*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_4			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (4*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_5			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (5*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_6			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (6*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_7			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (7*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_8			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (8*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_9			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (9*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_10			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (10*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_11			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (11*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_12			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (12*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_13			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (13*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_14			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (14*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_15			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (15*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_16			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (16*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_17			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (17*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_18			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (18*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_19			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (19*SDRAM_LCD_LAYER_SIZE))
#define SDRAM_LCD_LAYER_20			(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_LCD_LAYER_OFFSET + (20*SDRAM_LCD_LAYER_SIZE))



#define SDRAM_MEMORY_WIDTH      FMC_SDRAM_MEM_BUS_WIDTH_16
#define SDRAM_CAS_LATENCY       FMC_SDRAM_CAS_LATENCY_3
#define SDCLOCK_PERIOD       	FMC_SDRAM_CLOCK_PERIOD_3
#define SDRAM_READBURST         FMC_SDRAM_RBURST_DISABLE    /* Default configuration used with LCD */

#define REFRESH_COUNT			((uint32_t)0x0569)
#define SDRAM_TIMEOUT           ((uint32_t)0xFFFF)


/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)



//prototypes

void SDRAM_Initialization_sequence(uint32_t RefreshCount);
uint32_t SDRAM_MemoryTest(uint32_t page, uint32_t value);
void Fill_Buffer(uint32_t *pBuffer, uint32_t length, uint32_t value);

//write data - pointer, length, page - offset by page size
//void SDRAM_WriteDataByte(uint8_t *pBuffer, uint32_t numBytes, uint32_t page);
//void SDRAM_WriteDataHalfWord(uint16_t *pBuffer, uint32_t numBytes, uint32_t page);
//void SDRAM_WriteDataWord(uint32_t *pBuffer, uint32_t numBytes, uint32_t page);



#endif
