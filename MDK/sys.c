#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//m?t s? ch?c nang
void GPIO_Set(GPIO_TypeDef* GPIOx,u16 BITx,GPIOMode_TypeDef MODE,GPIOSpeed_TypeDef OSPEED)
{  
		GPIO_InitTypeDef  GPIO_InitStructure;
      
	
	if (GPIOx == GPIOA) {
		// Enable clock for GPIOA
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	} else if (GPIOx == GPIOB) {
		// Enable clock for GPIOB
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	} else if (GPIOx == GPIOC) {
		// Enable clock for GPIOC
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	}else if (GPIOx == GPIOD) {
		// Enable clock for GPIOD
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	}else if (GPIOx == GPIOE) {
		// Enable clock for GPIOE
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	}else if (GPIOx == GPIOF) {
		// Enable clock for GPIOF
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

	}else if (GPIOx == GPIOG) {
		// Enable clock for GPIOG
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

	}
	 
  GPIO_InitStructure.GPIO_Pin = BITx;			    //LED0-->PB.5 
  GPIO_InitStructure.GPIO_Mode = MODE;//GPIO_Mode_Out_PP; 	 
  GPIO_InitStructure.GPIO_Speed = OSPEED;//GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);			     //GPIOB.5
        
} 
//////////////////////////////////////////////////////////////////////////////////	 
const PinDescription g_APinDescription[]=
{

  { GPIOA, GPIO_Pin_0,RCC_APB2Periph_GPIOA, ADC_Channel_0, TIM5, TIM_Channel_1}, // 0     //      
  { GPIOA, GPIO_Pin_1,RCC_APB2Periph_GPIOA, ADC_Channel_1, TIM2, TIM_Channel_2}, // 1         // 
  { GPIOA, GPIO_Pin_2,RCC_APB2Periph_GPIOA, ADC_Channel_2, TIM2, TIM_Channel_3}, // 2
	{ GPIOA, GPIO_Pin_3,RCC_APB2Periph_GPIOA, ADC_Channel_3, TIM2, TIM_Channel_4}, // 3     //      
  { GPIOA, GPIO_Pin_4,RCC_APB2Periph_GPIOA, ADC_Channel_4, NULL, NULL}, // 4         // 
  { GPIOA, GPIO_Pin_5,RCC_APB2Periph_GPIOA, ADC_Channel_5, NULL, NULL}, // 5
	{ GPIOA, GPIO_Pin_6,RCC_APB2Periph_GPIOA, ADC_Channel_6, TIM3, TIM_Channel_1}, // 6     //      
  { GPIOA, GPIO_Pin_7,RCC_APB2Periph_GPIOA, ADC_Channel_7, TIM3, TIM_Channel_2}, // 7         // 
  { GPIOA, GPIO_Pin_8,RCC_APB2Periph_GPIOA, NULL, TIM1, TIM_Channel_1}, // 8
	{ GPIOA, GPIO_Pin_9,RCC_APB2Periph_GPIOA, NULL, TIM1, TIM_Channel_2}, // 9     //      
  { GPIOA, GPIO_Pin_10,RCC_APB2Periph_GPIOA,NULL, TIM1, TIM_Channel_3}, // 10         // 
  { GPIOA, GPIO_Pin_11,RCC_APB2Periph_GPIOA,NULL, TIM1, TIM_Channel_4}, // 11
	{ GPIOA, GPIO_Pin_12,RCC_APB2Periph_GPIOA,NULL, NULL, NULL}, // 12    //      
  { GPIOA, GPIO_Pin_13,RCC_APB2Periph_GPIOA,NULL, NULL, NULL}, // 13        // 
  { GPIOA, GPIO_Pin_14,RCC_APB2Periph_GPIOA,NULL, NULL, NULL}, // 14
	{ GPIOA, GPIO_Pin_15,RCC_APB2Periph_GPIOA,NULL, NULL, NULL}, // 15
	
	{ GPIOB, GPIO_Pin_0,RCC_APB2Periph_GPIOB, ADC_Channel_8, TIM3, TIM_Channel_3}, // 0     //      
  { GPIOB, GPIO_Pin_1,RCC_APB2Periph_GPIOB, ADC_Channel_9, TIM3, TIM_Channel_4}, // 1         // 
  { GPIOB, GPIO_Pin_2,RCC_APB2Periph_GPIOB,NULL, NULL, NULL}, // 2
	{ GPIOB, GPIO_Pin_3,RCC_APB2Periph_GPIOB, NULL, TIM2, TIM_Channel_2}, // 3     //      
  { GPIOB, GPIO_Pin_4,RCC_APB2Periph_GPIOB, NULL, TIM3, TIM_Channel_1}, // 4         // 
  { GPIOB, GPIO_Pin_5,RCC_APB2Periph_GPIOB, NULL, TIM3, TIM_Channel_2}, // 5
	{ GPIOB, GPIO_Pin_6,RCC_APB2Periph_GPIOB, NULL, TIM4, TIM_Channel_1}, // 6     //      
  { GPIOB, GPIO_Pin_7,RCC_APB2Periph_GPIOB, NULL, TIM4, TIM_Channel_2}, // 7         // 
  { GPIOB, GPIO_Pin_8,RCC_APB2Periph_GPIOB, NULL, TIM10, TIM_Channel_1}, // 8
	{ GPIOB, GPIO_Pin_9,RCC_APB2Periph_GPIOB, NULL, TIM11, TIM_Channel_1}, // 9     //      
  { GPIOB, GPIO_Pin_10,RCC_APB2Periph_GPIOB, NULL, TIM2, TIM_Channel_3}, // 10         // 
  { GPIOB, GPIO_Pin_11,RCC_APB2Periph_GPIOB, NULL, TIM2, TIM_Channel_4}, // 11
	{ GPIOB, GPIO_Pin_12,RCC_APB2Periph_GPIOB,NULL, NULL, NULL}, // 12    //      
  { GPIOB, GPIO_Pin_13,RCC_APB2Periph_GPIOB,NULL, NULL, NULL}, // 13        // 
  { GPIOB, GPIO_Pin_14,RCC_APB2Periph_GPIOB, NULL, TIM12, TIM_Channel_1}, // 14
	{ GPIOB, GPIO_Pin_15,RCC_APB2Periph_GPIOB, NULL, TIM12, TIM_Channel_2}, // 15
	
	{ GPIOC, GPIO_Pin_0,RCC_APB2Periph_GPIOC, ADC_Channel_10, NULL, NULL}, // 0     //      
  { GPIOC, GPIO_Pin_1,RCC_APB2Periph_GPIOC, ADC_Channel_11, NULL, NULL}, // 1         // 
  { GPIOC, GPIO_Pin_2,RCC_APB2Periph_GPIOC, ADC_Channel_12, NULL, NULL}, // 2
	{ GPIOC, GPIO_Pin_3,RCC_APB2Periph_GPIOC, ADC_Channel_13, NULL, NULL}, // 3     //      
  { GPIOC, GPIO_Pin_4,RCC_APB2Periph_GPIOC, ADC_Channel_14, NULL, NULL}, // 4         // 
  { GPIOC, GPIO_Pin_5,RCC_APB2Periph_GPIOC, ADC_Channel_14, NULL, NULL}, // 5
	{ GPIOC, GPIO_Pin_6,RCC_APB2Periph_GPIOC, NULL, TIM8, TIM_Channel_1}, // 6     //      
  { GPIOC, GPIO_Pin_7,RCC_APB2Periph_GPIOC, NULL, TIM8, TIM_Channel_2}, // 7         // 
  { GPIOC, GPIO_Pin_8,RCC_APB2Periph_GPIOC, NULL, TIM8, TIM_Channel_3}, // 8
	{ GPIOC, GPIO_Pin_9,RCC_APB2Periph_GPIOC, NULL, TIM8, TIM_Channel_4}, // 9     //      
  { GPIOC, GPIO_Pin_10,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 10         // 
  { GPIOC, GPIO_Pin_11,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 11
	{ GPIOC, GPIO_Pin_12,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 12    //      
  { GPIOC, GPIO_Pin_13,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 13        // 
  { GPIOC, GPIO_Pin_14,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 14
	{ GPIOC, GPIO_Pin_15,RCC_APB2Periph_GPIOC,NULL, NULL, NULL}, // 15
	
	{ GPIOD, GPIO_Pin_0,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 0     //      
  { GPIOD, GPIO_Pin_1,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 1         // 
  { GPIOD, GPIO_Pin_2,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 2
	{ GPIOD, GPIO_Pin_3,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 3     //      
  { GPIOD, GPIO_Pin_4,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 4         // 
  { GPIOD, GPIO_Pin_5,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 5
	{ GPIOD, GPIO_Pin_6,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 6     //      
  { GPIOD, GPIO_Pin_7,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 7         // 
  { GPIOD, GPIO_Pin_8,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 8
	{ GPIOD, GPIO_Pin_9,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 9     //      
  { GPIOD, GPIO_Pin_10,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 10         // 
  { GPIOD, GPIO_Pin_11,RCC_APB2Periph_GPIOD,NULL, NULL, NULL}, // 11
	{ GPIOD, GPIO_Pin_12,RCC_APB2Periph_GPIOD, NULL, TIM4, TIM_Channel_1}, // 12    //      
  { GPIOD, GPIO_Pin_13,RCC_APB2Periph_GPIOD, NULL, TIM4, TIM_Channel_2}, // 13        // 
  { GPIOD, GPIO_Pin_14,RCC_APB2Periph_GPIOD, NULL, TIM4, TIM_Channel_3}, // 14
	{ GPIOD, GPIO_Pin_15,RCC_APB2Periph_GPIOD, NULL, TIM4, TIM_Channel_4}, // 15
	
	{ GPIOE, GPIO_Pin_0,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 0     //      
  { GPIOE, GPIO_Pin_1,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 1         // 
  { GPIOE, GPIO_Pin_2,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 2
	{ GPIOE, GPIO_Pin_3,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 3     //      
  { GPIOE, GPIO_Pin_4,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 4         // 
  { GPIOE, GPIO_Pin_5,RCC_APB2Periph_GPIOE, NULL, TIM6, TIM_Channel_1}, // 5
	{ GPIOE, GPIO_Pin_6,RCC_APB2Periph_GPIOE, NULL, TIM6, TIM_Channel_2}, // 6     //      
  { GPIOE, GPIO_Pin_7,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 7         // 
  { GPIOE, GPIO_Pin_8,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 8
	{ GPIOE, GPIO_Pin_9,RCC_APB2Periph_GPIOE, NULL, TIM1, TIM_Channel_1}, // 9     //      
  { GPIOE, GPIO_Pin_10,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 10         // 
  { GPIOE, GPIO_Pin_11,RCC_APB2Periph_GPIOE, NULL, TIM1, TIM_Channel_2}, // 11
	{ GPIOE, GPIO_Pin_12,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 12    //      
  { GPIOE, GPIO_Pin_13,RCC_APB2Periph_GPIOE, NULL, TIM1, TIM_Channel_3}, // 13        // 
  { GPIOE, GPIO_Pin_14,RCC_APB2Periph_GPIOE, NULL, TIM1, TIM_Channel_4}, // 14
	{ GPIOE, GPIO_Pin_15,RCC_APB2Periph_GPIOE,NULL, NULL, NULL}, // 15
	
	{ GPIOF, GPIO_Pin_0,RCC_APB2Periph_GPIOF}, // 0     //      
  { GPIOF, GPIO_Pin_1,RCC_APB2Periph_GPIOF}, // 1         // 
  { GPIOF, GPIO_Pin_2,RCC_APB2Periph_GPIOF}, // 2
	{ GPIOF, GPIO_Pin_3,RCC_APB2Periph_GPIOF}, // 3     //      
  { GPIOF, GPIO_Pin_4,RCC_APB2Periph_GPIOF}, // 4         // 
  { GPIOF, GPIO_Pin_5,RCC_APB2Periph_GPIOF}, // 5
	{ GPIOF, GPIO_Pin_6,RCC_APB2Periph_GPIOF}, // 6     //      
  { GPIOF, GPIO_Pin_7,RCC_APB2Periph_GPIOF}, // 7         // 
  { GPIOF, GPIO_Pin_8,RCC_APB2Periph_GPIOF}, // 8
	{ GPIOF, GPIO_Pin_9,RCC_APB2Periph_GPIOF}, // 9     //      
  { GPIOF, GPIO_Pin_10,RCC_APB2Periph_GPIOF}, // 10         // 
  { GPIOF, GPIO_Pin_11,RCC_APB2Periph_GPIOF}, // 11
	{ GPIOF, GPIO_Pin_12,RCC_APB2Periph_GPIOF}, // 12    //      
  { GPIOF, GPIO_Pin_13,RCC_APB2Periph_GPIOF}, // 13        // 
  { GPIOF, GPIO_Pin_14,RCC_APB2Periph_GPIOF}, // 14
	{ GPIOF, GPIO_Pin_15,RCC_APB2Periph_GPIOF}, // 15		//95
} ;
//********************************************************************************  
void pinMode(u32 PINx,u32 MODE)
{  
   //u32 pinpos=0,pos=0,curpin=0;
	
	 GPIO_TypeDef *GPIOx = g_APinDescription[PINx].pPort;
	 uint16_t BITx = g_APinDescription[PINx].ulPin;
	 GPIO_InitTypeDef GPIO_InitStructure;

	 RCC_APB2PeriphClockCmd(g_APinDescription[PINx].ulPeripheral,ENABLE);

  GPIO_InitStructure.GPIO_Pin = BITx;
	
	if (MODE == INPUT) {
		// 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	} else if (MODE == INPUT_PULLUP) {
		// 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	} else if (MODE == INPUT_PULLDOWN) {
		// 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

	}else if (MODE == OUTPUT) {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	}else if (MODE == OUTPUT_OD) {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	} else if (MODE == AF_OD) {
		//
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	}else if (MODE == AF_PP) {
		// 
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	}else if (MODE == AN_INPUT) {
		// 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

	}
	GPIO_Init(GPIOx, &GPIO_InitStructure);  
	
        
} 

void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
  /* Handle */

   if ( ulVal == HIGH )
  {
    g_APinDescription[ulPin].pPort->BSRR = g_APinDescription[ulPin].ulPin;
  }
  else
  {
    g_APinDescription[ulPin].pPort->BRR = g_APinDescription[ulPin].ulPin;
  }
}

int digitalRead( uint32_t ulPin )
{
	
	//return (digitalPinToPort(ulPin)->IDR &digitalPinToBitMask(ulPin))==0? 0:1 ;
	return GPIO_ReadInputDataBit(g_APinDescription[ulPin].pPort, g_APinDescription[ulPin].ulPin);
}
///////////////////////////////////

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
