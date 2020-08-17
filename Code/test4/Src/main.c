/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint16_t rawValue;
void read_ultra(void);
int rising_edge = 0;
uint32_t value_rising;
uint32_t value_falling;
double volatile distance=0;
double volatile temp;
void stepper(int direction);
void steper_degree(int teta,int direction);
int Steps=0;
int counter;
int T=0;
int volatile Flag_distance=0;
int max_output = 270;
int min_output = 0;
int volatile current_output =0;
int volatile output;
float error = 0;
void Send_Stats();
unsigned char myRxData[20];
int lux = 0;
char Command[20];
int temp_counter2=0;
int Ter=0;
void Compare_Strigns();
int stats_flag=0;
int AutoMode_flag=0;
int sp = 27;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim2);
	HAL_ADC_Start_IT(&hadc1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_UART_Receive_DMA(&huart4, myRxData, 1);

  while (1)
  {
		
		
		
		//reading the distance
		read_ultra();
		HAL_Delay(50);
		//if users asks for status we will send it 
		if(stats_flag==1)
		{
			Send_Stats();
			HAL_Delay(10);
			stats_flag=0;
		}
		else if(stats_flag==2)
		{
			//if the user asks for automode we change it to on
			stats_flag=0;
			AutoMode_flag=0;
		}
		else if (stats_flag==3)
		{
			//if the user asks for automode we change it to off
			stats_flag=0;
			AutoMode_flag=1;
		}
		if(AutoMode_flag==0)
		{
			//if automode is off the motor decides how much it should rotate  based on the setpoint
			stats_flag=0;
			if(distance < 10 && current_output != 0)
			{
				steper_degree(current_output,1);
				current_output = 0;
			}
			if(distance>10)
			{
				HAL_ADC_ConvCpltCallback(&hadc1);
				error=27-temp;
				output= (float) error/5*270;
				if(output <= 270 && output >= 0)
				{
					if(output - current_output > 0 ){
						steper_degree(output-current_output,0);
						current_output = output;
					}
					else{
						steper_degree(current_output - output,1);
						current_output = output;
					}
				}
				else if(output < 0){
					steper_degree(current_output,1);
					current_output = 0;
				}
				else{
					steper_degree(270 - current_output,0);
					current_output = 270;
				}
			}
			/* USER CODE END WHILE */
		}
    /* USER CODE BEGIN 3 */
		else 
		{
				//if automode is off the motor decides based on the given setpoint or the default setpoint
				stats_flag=0;
				HAL_ADC_ConvCpltCallback(&hadc1);
				error=sp-temp;
				output= (float) error/5*270;
				if(output <= 270 && output >= 0)
				{
					if(output - current_output > 0 ){
						steper_degree(output-current_output,0);
						current_output = output;
					}
					else{
						steper_degree(current_output - output,1);
						current_output = output;
					}
				}
				else if(output < 0){
					steper_degree(current_output,1);
					current_output = 0;
				}
				else{
					steper_degree(270 - current_output,0);
					current_output = 270;
				}
		}
	
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	rawValue = HAL_ADC_GetValue(hadc);
	temp = (double) rawValue/4095*2920/10;
}

void read_ultra(void)
{
	HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim3);
}

void steper_degree(int teta,int direction)
{
	//based on teta finds how many steps the motor should take
	if(teta!=0)
	{	
	counter = ( (float) teta / 90 )*500;
	for(int i=0;i<counter;i++)
	{
			stepper(direction);
			HAL_Delay(1);
	}
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(rising_edge == 0) //rising not detected
	{
		value_rising = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);
		rising_edge = 1;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
	}
	else if(rising_edge == 1) //rising detected
	{
		value_falling = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_1);	
		
		if(value_falling > value_rising)
		{
				distance = (double)((value_falling - value_rising)*0.034/2);
		}
		else
		{
				distance = (double)(((0xffffffff - value_rising ) + value_falling)*0.034/2);
		}
		rising_edge = 0;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Stop_IT(&htim5,TIM_CHANNEL_1);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_RESET);
		HAL_TIM_IC_Start_IT(&htim5,TIM_CHANNEL_1);
		HAL_TIM_Base_Stop_IT(&htim3);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//we use this to empty our string
	if(Ter==0)
	{
		for(int i = 0 ; i <20 ;i++)
		{
			Command[i]=10;
		}
	}
	//user should use the newline in arduino commands so we be able to recognize the command's end
	//then we will write the command in our buffer until we reach end symbole
	if(myRxData[0]!=10 )
	{
		Command[Ter]= myRxData[0];
		Ter++;
	}
	else{
		//this will help us to use string's functions
		Command[Ter] = '\0';
		Ter=0;
		Compare_Strigns();
	}
}
void Compare_Strigns()
{
	//we used strcmp for comparing strings 
	if(strcmp("Status",Command)==0)
		stats_flag=1;
	else if(strcmp("Turn on Auto Mode",Command)==0)
	{
		char buffer[50];
		sprintf(buffer,"Auto Mode turned on \n");
		HAL_UART_Transmit(&huart4,(uint8_t*) buffer,strlen((char*)buffer),20);
		stats_flag=2;
	}
	else if(strcmp("Turn off Auto Mode",Command)==0)
	{
		char buffer[50];
		sprintf(buffer,"Auto Mode turned off \n");
		HAL_UART_Transmit(&huart4,(uint8_t*) buffer,strlen((char*)buffer),20);
		stats_flag=3;
	}
	else 
	{
		//the 12 and 13 charachter should be the temperature that user wants
		sp = (int)(Command[12]-'0')*10+(int) ( Command[13]-'0') ;
		char buffer[50];
		sprintf(buffer,"Temp set to %d deg \n",sp);
		HAL_UART_Transmit(&huart4,(uint8_t*) buffer,strlen((char*)buffer),20);
	}
	
}

void Send_Stats()
{
		//making a buffer to write data in it 
		char buffer[50];
		//after with %f we will send the temp
		sprintf(buffer,"Temp = %2f degree \n", temp);
		HAL_UART_Transmit(&huart4,(uint8_t*) buffer,strlen((char*)buffer),10);
		HAL_Delay(10);
		sprintf(buffer,"Motor_Pos = %d degree \n", current_output);
		HAL_UART_Transmit(&huart4,(uint8_t*) buffer,strlen((char*)buffer),10);
		HAL_Delay(10);
		//if the distance is less than 10 the door is closed and 
		if(distance>10)
		{
				HAL_UART_Transmit(&huart4,(uint8_t*) "Door is open \n" ,strlen((char*)"Door is open \n"),10);
		}
		else 
		{
			HAL_UART_Transmit(&huart4,(uint8_t*) "Door is close \n" ,strlen((char*)"Door is close \n"),10);
		}
		HAL_Delay(10);
		//based on thte automodeflag user receives the proper message
		if(AutoMode_flag==0)
		{
			HAL_UART_Transmit(&huart4,(uint8_t*) "Auto Mode is ON \n" ,strlen((char*)"Auto Mode is ON \n"),10);
		}
		
		else
		{
			HAL_UART_Transmit(&huart4,(uint8_t*) "Auto Mode is OFF \n" ,strlen((char*)"Auto Mode is OFF \n"),10);
		}
		HAL_Delay(10);
}



void stepper(int direction)
{
		//this is how one step works
		switch(Steps)
		{
			case 0 :
				HAL_GPIO_WritePin(Blue_GPIO_Port,Blue_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(Pink_GPIO_Port,Pink_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Orange_GPIO_Port,Orange_Pin,GPIO_PIN_RESET);
				T=1;
				break;
			case 1 :
				HAL_GPIO_WritePin(Blue_GPIO_Port,Blue_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Pink_GPIO_Port,Pink_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Orange_GPIO_Port,Orange_Pin,GPIO_PIN_RESET);
				T=2;
				break;
			case 2 :
				HAL_GPIO_WritePin(Blue_GPIO_Port,Blue_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Pink_GPIO_Port,Pink_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(Orange_GPIO_Port,Orange_Pin,GPIO_PIN_RESET);
				T=3;
				break;
			case 3 :
				HAL_GPIO_WritePin(Blue_GPIO_Port,Blue_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Pink_GPIO_Port,Pink_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(Orange_GPIO_Port,Orange_Pin,GPIO_PIN_SET);
				T=4;
				break;
			
		}
		
		if(direction==0)//clockwise
		{
			Steps++;
		}
		else
			Steps--;
		if(Steps > 3)
			Steps = 0;
		if(Steps < 0)
			Steps = 3;
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
