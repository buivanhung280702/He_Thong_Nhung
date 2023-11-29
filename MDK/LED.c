#include "LED.h"

#include "sys.h"

void LED_init(void){
	
// GPIO_InitTypeDef  GPIO_InitStructure; 		
//	
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	    //PB,PE		
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			    //LED0-->PB.5 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
//  GPIO_Init(GPIOB, &GPIO_InitStructure);			     //GPIOB.5		
	GPIO_Set(GPIOB,GPIO_Pin_5|GPIO_Pin_6,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  GPIO_ResetBits(GPIOB,GPIO_Pin_5);					//PB.5 =0
	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //LED1-->PE.5
//  GPIO_Init(GPIOE, &GPIO_InitStructure);	  	       
	GPIO_Set(GPIOE,GPIO_Pin_5,GPIO_Mode_IPU,GPIO_Speed_50MHz);
  //GPIO_ResetBits(GPIOE,GPIO_Pin_5); 			 //PE.5 =0  
}


