/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include <stdlib.h>


#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "lcd_12864_dfrobot.h"
#include "sprite.h"
#include "Sound.h"
#include "joystick.h"
#include "bitmap.h"
#include "eeprom.h"
#include "score.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint32_t gCounter = 0x00;

/* USER CODE END 0 */

int main(void)
{

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI1_Init();
	MX_I2C1_Init();
	MX_ADC1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();

	/* USER CODE BEGIN 2 */
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	LCD_Config();					//config 128x64 display
	Joystick_Config();				//DMA stream for ADC - A1
	Sound_Init();					//timers and sound
	Sprite_Init();					//game init
	LCD_BacklightOn();				//backlight

	HAL_Delay(100);					//wait a bit

	EEPROM_init();					//simple read/write check

	/////////////////////////////////////////////////
	//Clear high score. comment out if not needed
//		int result = Score_Init();
//		if (result < 0)
//			while (1){};
	//////////////////////////////////////////////////


	Sprite_SetGameOverFlag();		//start with game over

	HAL_Delay(500);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (Sprite_GetGameOverFlag() == 1)
		{
			Sound_Play_GameOver();

			//evaluate the high score and current score
			if (Sprite_GetGameScore() > Score_GetHighScore())
			{
				while(Sprite_GetGameOverFlag() == 1)
				{
					Score_DisplayNewHighScore(Sprite_GetGameScore(), Sprite_GetGameLevel());
					HAL_Delay(1000);
					LCD_Clear(0x00);
					HAL_Delay(1000);
				}

				//update the high score and level here
				Score_SetHighScore(Sprite_GetGameScore());
				Score_SetMaxLevel(Sprite_GetGameLevel());

				Sprite_SetGameOverFlag();
			}

			HAL_Delay(2000);
		}


		///////////////////////////////////////////////////
		//Button press while game over flag is set
		//will clear the game over flag, otherwise, it fires
		while (Sprite_GetGameOverFlag() == 1)
		{
			uint8_t buffer[SCORE_PLAYER_NAME_SIZE] = {0x00};
			uint8_t buffer2[16] = {0x00};
			uint16_t highScore = Score_GetHighScore();
			uint8_t level = Score_GetMaxLevel();
			uint8_t len = Score_GetPlayerName(buffer);

			LCD_DrawStringKernLength(1, 3, buffer, len);

			int n = sprintf((char*)buffer2, "Score:%d", highScore);
			LCD_DrawStringKernLength(2, 3, buffer2, n);

			n = sprintf((char*)buffer2, "Level:%d", level);
			LCD_DrawStringKernLength(3, 3, buffer2, n);

			LCD_DrawStringKern(5, 3, " Press Button");

			HAL_Delay(1000);
			LCD_Clear(0x00);
			HAL_Delay(1000);

			Sprite_Init();                  //reset and clear all flags
		}


		///////////////////////////////////////////
		//launch any new missiles from player? - flag set in the button isr
		if (Sprite_GetMissileLaunchFlag() == 1)
		{
			Sprite_ClearMissileLaunchFlag();
			Sprite_Missile_Launch();
		}


		///////////////////////////////////////////////////
		//Read the joystick - up, down, left, right
		//and update player orientation and thruster
		JoystickPosition_t pos = Joystick_GetPosition();

		switch(pos)
		{
			case JOYSTICK_UP:		Sprite_PlayerFireThruster();		break;
			case JOYSTICK_DOWN: 	Sprite_PlayerFlipRotation();		break;
			case JOYSTICK_LEFT:		Sprite_PlayerRotateCCW();			break;
			case JOYSTICK_RIGHT:	Sprite_PlayerRotateCW();			break;
			case JOYSTICK_PRESS:										break;
			case JOYSTICK_NONE:											break;
			default:													break;
		}

		//launch a drone ever 50 game loops
		if (!(gCounter % 50))
		{
			//random number 0 -2, launch the appropriate drone
			volatile int result = rand() % 3;
			switch (result)
			{
				case 0: 	Sprite_Drone_Launch(DRONE_TYPE_SMALL);		break;
				case 1: 	Sprite_Drone_Launch(DRONE_TYPE_MEDIUM);		break;
				case 2: 	Sprite_Drone_Launch(DRONE_TYPE_LARGE);		break;
				default:	Sprite_Drone_Launch(DRONE_TYPE_SMALL);		break;
			}
		}

		Sprite_Player_Move();		//move player
		Sprite_Astroid_Move();		//move enemy
		Sprite_Missile_Move();		//move missle
		Sprite_Drone_Move();		//move the drone if there is one

		Sprite_UpdateDisplay();	//update the display

		gCounter++;

		HAL_Delay(200);
	}

  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */
	static uint32_t counter = 0x00;

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1)
	{
		HAL_IncTick();

		//increments at 1khz - set the backlight on 20%
		if (!(counter % 5))
		{
			LCD_BacklightOn();
		}
		else
		{
			LCD_BacklightOff();
		}

		counter++;

	}
	/* USER CODE BEGIN Callback 1 */
	////////////////////////////////////////////
	//Timer TIM2 - Not Used For Now
	if (htim->Instance == TIM2)
	{

	}

	//////////////////////////////////////
	//Timer3 - 11khz timer
	//Sound timer.  Runs when sound is playing.
	//Timer stops when sound array is done.
	//See sound.h.  NOTE: in tim.c, check the prescale
	//and reload values as 15 and 362 to get 11khz.
	if (htim->Instance == TIM3)
	{
		Sound_InterruptHandler();      //main
	}

/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
