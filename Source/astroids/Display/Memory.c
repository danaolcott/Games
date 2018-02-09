/*
Memory Driver / Controller for SDRAM

Function definitions from the BSP for SDRAM
in the STM example projects


*/

#include "Memory.h"


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>




void SDRAM_Initialization_sequence(uint32_t RefreshCount)
{
  __IO uint32_t tmpmrd =0;
  
  FMC_SDRAM_CommandTypeDef Command;


  /* Step 1:  Configure a clock configuration enable command */
  Command.CommandMode             = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(100);

  /* Step 3: Configure a PALL (precharge all) command */ 
  Command.CommandMode             = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);
  
  /* Step 4: Configure an Auto Refresh command */ 
  Command.CommandMode             = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 4;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);
  
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  
  Command.CommandMode             = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);
  
  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, RefreshCount);
}



//////////////////////////////////////////////////
//Memory test for SDRAM
//Fills a page with a value and reads it back.  Page size is
//in bytes.  The value written / read is 4 bytes
//returns 0 if ok
uint32_t SDRAM_MemoryTest(uint32_t page, uint32_t value)
{
	uint32_t index = 0;
	uint32_t aTxBuffer[SDRAM_PAGE_SIZE / 4];
	uint32_t aRxBuffer[SDRAM_PAGE_SIZE / 4];
	__IO uint32_t status = 0;
	uint32_t i;
	uint32_t pageOffset = page * SDRAM_PAGE_SIZE;

	//fill the buffer
	Fill_Buffer(aTxBuffer, SDRAM_PAGE_SIZE / 4, value);

	//write the value to memory
	for (i = 0 ; i < 1000 ; i++)
	{

		for (index = 0 ; index < SDRAM_PAGE_SIZE / 4 ; index++)
		{
			uint8_t val0 = aTxBuffer[index] & 0xFF;
			uint8_t val1 = (aTxBuffer[index] >> 8) & 0xFF;
			uint8_t val2 = (aTxBuffer[index] >> 16) & 0xFF;
			uint8_t val3 = (aTxBuffer[index] >> 24) & 0xFF;

			*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_READ_WRITE_OFFSET + pageOffset + 4*index + 0) = val0;
			*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_READ_WRITE_OFFSET + pageOffset + 4*index + 1) = val1;
			*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_READ_WRITE_OFFSET + pageOffset + 4*index + 2) = val2;
			*(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_READ_WRITE_OFFSET + pageOffset + 4*index + 3) = val3;

		}

	}

	//read the data back from sdram
	for (i = 0 ; i < 1000 ; i++)
	{
		for (index = 0; index < SDRAM_PAGE_SIZE / 4; index++)
		{
			aRxBuffer[index] = *(__IO uint32_t*) (SDRAM_BASE_ADDR + SDRAM_READ_WRITE_OFFSET + pageOffset + 4*index);
		}
	}

	//check the data
	for (index = 0; (index < SDRAM_PAGE_SIZE / 4) && (status == 0); index++)
	{
		if (aRxBuffer[index] != aTxBuffer[index])
		{
			status++;
		}
	}

	return status;

}



void Fill_Buffer(uint32_t *pBuffer, uint32_t length, uint32_t value)
{
	uint32_t tmpIndex = 0;

	/* Put in global buffer different values */
	for (tmpIndex = 0; tmpIndex < length ; tmpIndex++ )
	{
		pBuffer[tmpIndex] = value;
	}
}


