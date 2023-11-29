#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "i2c.h"
#include "i2c_lcd.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "dht11.h"

EventGroupHandle_t eventhdl; 

#define EVENT0 (1<<0)
#define EVENT1 (1<<1)
#define EVENT2 (1<<2)
#define EVENT_ALLS ((EVENT2<<1) - 1)

void TaskMain(void *x);
void TaskA(void *x);
void TaskB(void *x);
void TaskC(void *x);
void Fn_GPIO_Init(void);
void usart_SendChar(char _chr);
void usart_SendStr(char *str);

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	Fn_GPIO_Init();
	DHT11_Init();
	I2C_LCD_Init();
	
	xTaskCreate(TaskMain, "TaskMain", 256, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(TaskA, "TaskA", 256, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(TaskB, "TaskB", 256, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(TaskC, "TaskC", 256, NULL, tskIDLE_PRIORITY, NULL);
	
	vTaskStartScheduler();
	return 0;
}

void Fn_GPIO_Init(void){
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//button
	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	//Tx
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	//Rx
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	//usart
	usart.USART_BaudRate = 9600;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart);
	USART_Cmd(USART1, ENABLE);	
}

uint16_t counter = 0; 
uint8_t sttOld = 1, sttNew = 1;
uint8_t temp  = 0, humi = 0;
char buffer[20];

void TaskMain(void *x){
	eventhdl = xEventGroupCreate();
	while(1){
		sttOld = sttNew; 
		sttNew = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
		
		if(sttOld == 1 && sttNew == 0){
			counter++; 
		}
		if(counter % 3 == 0){
				xEventGroupSetBits(eventhdl, EVENT0);
			}else if(counter % 3 == 1){
				xEventGroupSetBits(eventhdl, EVENT1);
			}else{
				xEventGroupSetBits(eventhdl, EVENT2);
			}
		vTaskDelay(20);
	}
}

void TaskA(void *x){
	EventBits_t event; 
	while(1){
		event = xEventGroupWaitBits(eventhdl, EVENT_ALLS, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT1){
			DHT11_Read_Data(&temp,&humi);
			usart_SendStr("LCD + Serial:\t");
			I2C_LCD_Clear();
			I2C_LCD_Puts("LCD + Serial");
			I2C_LCD_NewLine();
			sprintf(buffer, "T: %d, H: %d", temp, humi);
			I2C_LCD_Puts(buffer);
			usart_SendStr(buffer);
			usart_SendStr("\n");
			delay_ms(300);
		}
	}
}

void TaskB(void *x){
	EventBits_t event; 
	while(1){
		event = xEventGroupWaitBits(eventhdl, EVENT_ALLS, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT0){
			DHT11_Read_Data(&temp,&humi);
			usart_SendStr("LCD:\t");
			I2C_LCD_Clear();
			I2C_LCD_Puts("LCD:");
			I2C_LCD_NewLine();
			sprintf(buffer, "T: %d, H: %d", temp, humi);
			I2C_LCD_Puts(buffer);
			usart_SendStr("\n");
			delay_ms(300);
		}
	}
}

void TaskC(void *x){
	EventBits_t event; 
	while(1){
		event = xEventGroupWaitBits(eventhdl, EVENT_ALLS, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT2){
			DHT11_Read_Data(&temp,&humi);
			usart_SendStr("Serial:\t");
			I2C_LCD_Clear();
			sprintf(buffer, "T: %d, H: %d", temp, humi);
			I2C_LCD_Puts("Serial");
			usart_SendStr(buffer);
			usart_SendStr("\n");
			delay_ms(300);
		}
	}
}

void usart_SendChar(char _chr){
	USART_SendData(USART1, _chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void usart_SendStr(char *str){
	while(*str != NULL){
		usart_SendChar(*str++);
	}
}

