/**	
 * |----------------------------------------------------------------------
 * | 	Pins_PA9PA10,	//USART1
			Pins_PB6PB7,	////USART1
			Pins_PA2PA3,	//USART2
			Pins_PD5PD6,	//USART2
			Pins_PB10PB11,	//USART3
			Pins_PC10PC11,	//USART3//UART4
			Pins_PD8PD9,	//USART3
			Pins_PA0PA1,	//UART4
			Pins_PC12PD2,	//UART5
			Pins_PC6PC7,	//USART6
			Pins_PG14PG9,	//USART6
			Pins_PB8PE7,	//UART7
			Pins_PF7PF6,	//UART7
			Pins_PE1PE0		//UART8
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "usart.h"
#include "stdio.h"
/**
 * Internal USART struct
 */
typedef struct {
	int8_t *Buffer;
	uint16_t Size;
	uint16_t Num;
	uint16_t In;
	uint16_t Out;
} USART_t;

// Th¨ºm m? sau ?ay ?? h? tr? ch?c n?ng printf, m¨¤ kh?ng c?n ph?i ch?n MicroLIB s? d?ng  
//	u8 t;
//printf("t:%d\r\n",t);
/* We need to implement own __FILE struct */
/* FILE struct is used from __FILE */
struct __FILE {
    int dummy;
};
 
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
FILE __stdout;
 
int fputc(int ch, FILE *f) {
    /* Do your stuff here */
    /* Send your custom byte */
    /* Send byte to USART */
    USART_Putc(USART2, ch);
    
    /* If everything is OK, you have to return character written */
    return ch;
    /* If character is not correct, you can return EOF (-1) to stop writing */
    //return -1;
}

/* Set variables for buffers */
#ifdef USE_USART1
int8_t USART1_Buffer[USART1_BUFFER_SIZE];
#endif
#ifdef USE_USART2
int8_t USART2_Buffer[USART2_BUFFER_SIZE];
#endif
#ifdef USE_USART3
int8_t USART3_Buffer[USART3_BUFFER_SIZE];
#endif
#ifdef USE_UART4
int8_t UART4_Buffer[UART4_BUFFER_SIZE];
#endif
#ifdef USE_UART5
int8_t UART5_Buffer[UART5_BUFFER_SIZE];
#endif
#ifdef USE_USART6
int8_t USART6_Buffer[USART6_BUFFER_SIZE];
#endif
#ifdef USE_UART7
int8_t UART7_Buffer[UART7_BUFFER_SIZE];
#endif
#ifdef USE_UART8
int8_t UART8_Buffer[UART8_BUFFER_SIZE];
#endif

#ifdef USE_USART1
USART_t F4_USART1 = {USART1_Buffer, USART1_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_USART2
USART_t F4_USART2 = {USART2_Buffer, USART2_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_USART3
USART_t F4_USART3 = {USART3_Buffer, USART3_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_UART4
USART_t F4_UART4 = {UART4_Buffer, UART4_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_UART5
USART_t F4_UART5 = {UART5_Buffer, UART5_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_USART6
USART_t F4_USART6 = {USART6_Buffer, USART6_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_UART7
USART_t F4_UART7 = {UART7_Buffer, UART7_BUFFER_SIZE, 0, 0, 0};
#endif
#ifdef USE_UART8
USART_t F4_UART8 = {UART8_Buffer, UART8_BUFFER_SIZE, 0, 0, 0};
#endif

GPIO_InitTypeDef GPIO_InitStruct;

void USART1_InitPins(USART_PinsPack_t pinspack);
void USART2_InitPins(USART_PinsPack_t pinspack);
void USART3_InitPins(USART_PinsPack_t pinspack);
void UART4_InitPins(USART_PinsPack_t pinspack);
void UART5_InitPins(USART_PinsPack_t pinspack);
void USART6_InitPins(USART_PinsPack_t pinspack);
void UART7_InitPins(USART_PinsPack_t pinspack);
void UART8_InitPins(USART_PinsPack_t pinspack);
void USART_INT_InsertToBuffer(USART_t* u, uint8_t c);
USART_t* USART_INT_GetUsart(USART_TypeDef* USARTx);
uint8_t USART_INT_GetSubPriority(USART_TypeDef* USARTx);
uint8_t USART_BufferFull(USART_TypeDef* USARTx);

void USARTx_Init(USART_TypeDef* USARTx, USART_PinsPack_t pinspack, uint32_t baudrate) {
	/**
	 * Initialization structures declared
	 *
	 * USART: Universal Synchronous/Asynchronous Receiver/Transmitter
	 * NVIC: Nested Vector Interrupt Controller
	 */
	USART_InitTypeDef 	USART_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;

	/* Set default GPIO settings */
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	
	/**
	 * Default settings:
	 * 
	 * Set Baudrate to value you pass to function
	 * Disable Hardware Flow control
	 * Set Mode To TX and RX, so USART will work in full-duplex mode
	 * Disable parity bit
	 * Set 1 stop bit
	 * Set Data bits to 8
	 */
	USART_InitStruct.USART_BaudRate = baudrate;
	
	/*
	 * Initialize USARTx pins
	 * Set channel for USARTx NVIC
	 */
#ifdef USE_USART1
	if (USARTx == USART1) {
		USART1_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = USART1_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = USART1_MODE;
		USART_InitStruct.USART_Parity = USART1_PARITY;
		USART_InitStruct.USART_StopBits = USART1_STOP_BITS;
		USART_InitStruct.USART_WordLength = USART1_WORD_LENGTH;
	}
#endif
#ifdef USE_USART2
	if (USARTx == USART2) {
		USART2_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = USART2_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = USART2_MODE;
		USART_InitStruct.USART_Parity = USART2_PARITY;
		USART_InitStruct.USART_StopBits = USART2_STOP_BITS;
		USART_InitStruct.USART_WordLength = USART2_WORD_LENGTH;
	}
#endif
#ifdef USE_USART3
	if (USARTx == USART3) {
		USART3_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = USART3_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = USART3_MODE;
		USART_InitStruct.USART_Parity = USART3_PARITY;
		USART_InitStruct.USART_StopBits = USART3_STOP_BITS;
		USART_InitStruct.USART_WordLength = USART3_WORD_LENGTH;
	}
#endif
#ifdef USE_UART4
	if (USARTx == UART4) {
		UART4_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = UART4_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = UART4_MODE;
		USART_InitStruct.USART_Parity = UART4_PARITY;
		USART_InitStruct.USART_StopBits = UART4_STOP_BITS;
		USART_InitStruct.USART_WordLength = UART4_WORD_LENGTH;
	}
#endif
#ifdef USE_UART5
	if (USARTx == UART5) {
		UART5_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = UART5_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = UART5_MODE;
		USART_InitStruct.USART_Parity = UART5_PARITY;
		USART_InitStruct.USART_StopBits = UART5_STOP_BITS;
		USART_InitStruct.USART_WordLength = UART5_WORD_LENGTH;
	}
#endif

#ifdef USE_UART7
	if (USARTx == UART7) {
		UART7_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = UART7_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = UART7_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = UART7_MODE;
		USART_InitStruct.USART_Parity = UART7_PARITY;
		USART_InitStruct.USART_StopBits = UART7_STOP_BITS;
		USART_InitStruct.USART_WordLength = UART7_WORD_LENGTH;
	}
#endif
#ifdef USE_UART8
	if (USARTx == UART8) {
		UART8_InitPins(pinspack);
		NVIC_InitStruct.NVIC_IRQChannel = UART8_IRQn;
		
		USART_InitStruct.USART_HardwareFlowControl = UART8_HARDWARE_FLOW_CONTROL;
		USART_InitStruct.USART_Mode = UART8_MODE;
		USART_InitStruct.USART_Parity = UART8_PARITY;
		USART_InitStruct.USART_StopBits = UART8_STOP_BITS;
		USART_InitStruct.USART_WordLength = UART8_WORD_LENGTH;
	}
#endif
	
	/* Disable */
	USART_Cmd(USARTx, DISABLE);
	/* Deinit first */
	USART_DeInit(USARTx);
	
	/* Init */
	USART_Init(USARTx, &USART_InitStruct);
	/* Enable */
	USART_Cmd(USARTx, ENABLE);
	
	/* Enable RX interrupt */
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

	/**
	 * Set Channel Cmd to enable. That will enable USARTx channel in NVIC
	 * Set NVIC_IRQChannelPreemptionPriority. This means high priority for USARTs
	 * USARTx with lower x has high subpriority
	 *
	 * Initialize NVIC
	 */
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = USART_NVIC_PRIORITY;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = USART_INT_GetSubPriority(USARTx);
	NVIC_Init(&NVIC_InitStruct);
}

uint8_t USART_Getc(USART_TypeDef* USARTx) {
	int8_t c = 0;
	USART_t* u = USART_INT_GetUsart(USARTx);
	
	/* Check if we have any data in buffer */
	if (u->Num > 0) {
		if (u->Out == u->Size) {
			u->Out = 0;
		}
		c = *(u->Buffer + u->Out);
		u->Out++;
		u->Num--;
	}
	return c;
}

uint16_t USART_Gets(USART_TypeDef* USARTx, char* buffer, uint16_t bufsize) {
	uint16_t i = 0;
	
	/* Check for any data on USART */
	if (USART_BufferEmpty(USARTx) || (!USART_FindCharacter(USARTx, '\n') && !USART_BufferFull(USARTx))) {
		return 0;
	}
	
	/* If available buffer size is more than 0 characters */
	while (i < (bufsize - 1)) {
		/* We have available data */
		buffer[i] = (char) USART_Getc(USARTx);
		/* Check for end of string */
		if (buffer[i] == '\n') {
			i++;
			/* Done */
			break;
		} else {
			i++;
		}
	}
	
	/* Add zero to the end of string */
	buffer[i] = 0;               

	return (i);
}

uint8_t USART_BufferEmpty(USART_TypeDef* USARTx) {
	USART_t* u = USART_INT_GetUsart(USARTx);
	return (u->Num == 0);
}

uint8_t USART_BufferFull(USART_TypeDef* USARTx) {
	USART_t* u = USART_INT_GetUsart(USARTx);
	return (u->Num == u->Size);
}

void USART_ClearBuffer(USART_TypeDef* USARTx) {
	USART_t* u = USART_INT_GetUsart(USARTx);
	
	u->Num = 0;
	u->In = 0;
	u->Out = 0;
}

uint8_t USART_FindCharacter(USART_TypeDef* USARTx, volatile char c) {
	uint16_t num, out;
	USART_t* u = USART_INT_GetUsart(USARTx);
	
	/* Temp variables */
	num = u->Num;
	out = u->Out;
	
	while (num > 0) {
		/* Check overflow */
		if (out == u->Size) {
			out = 0;
		}
		if (u->Buffer[out] == c) {
			/* Character found */
			return 1;
		}
		out++;
		num--;
	}
	
	/* Character is not in buffer */
	return 0;
}

void USART_Puts(USART_TypeDef* USARTx, char* str) {
	while (*str) {
		/* Send char by char */
		USART_Putc(USARTx, *str++);
	}
}

void USART_Putc(USART_TypeDef* USARTx, volatile char c) {
	/* Wait to be ready */
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
	/* Send data */
	USARTx->DR = (uint16_t)(c & 0x01FF);
}

/* Private functions */
void USART_INT_InsertToBuffer(USART_t* u, uint8_t c) {
	/* Still available space in buffer */
	if (u->Num < u->Size) {
		/* Check overflow */
		if (u->In == u->Size) {
			u->In = 0;
		}
		/* Add to buffer */
		u->Buffer[u->In] = c;
		u->In++;
		u->Num++;
	}
}

USART_t* USART_INT_GetUsart(USART_TypeDef* USARTx) {
	USART_t* u;
	
#ifdef USE_USART1
	if (USARTx == USART1) {
		u = &F4_USART1;
	}
#endif
#ifdef USE_USART2
	if (USARTx == USART2) {
		u = &F4_USART2;
	}
#endif
#ifdef USE_USART3
	if (USARTx == USART3) {
		u = &F4_USART3;
	}
#endif
#ifdef USE_UART4
	if (USARTx == UART4) {
		u = &F4_UART4;
	}
#endif
#ifdef USE_UART5
	if (USARTx == UART5) {
		u = &F4_UART5;
	}
#endif

#ifdef USE_UART7
	if (USARTx == UART7) {
		u = &F4_UART7;
	}
#endif
#ifdef USE_UART8
	if (USARTx == UART8) {
		u = &F4_UART8;
	}
#endif

	return u;
}

uint8_t USART_INT_GetSubPriority(USART_TypeDef* USARTx) {
	uint8_t u;
	
#ifdef USE_USART1
	if (USARTx == USART1) {
		u = 0;
	}
#endif
#ifdef USE_USART2
	if (USARTx == USART2) {
		u = 1;
	}
#endif
#ifdef USE_USART3
	if (USARTx == USART3) {
		u = 2;
	}
#endif
#ifdef USE_UART4
	if (USARTx == UART4) {
		u = 4;
	}
#endif
#ifdef USE_UART5
	if (USARTx == UART5) {
		u = 5;
	}
#endif

#ifdef USE_UART7
	if (USARTx == UART7) {
		u = 7;
	}
#endif
#ifdef USE_UART8
	if (USARTx == UART8) {
		u = 8;
	}
#endif
	
	return u;
}

#ifdef USE_USART1
void USART1_InitPins(USART_PinsPack_t pinspack) {	
	//Enable clock for USART1

	if (pinspack == Pins_PA9PA10) {
		// Enable clock for GPIOA
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,ENABLE);
      //Configure USART1 Tx (PA.09) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStruct);

		// Configure USART1 Rx (PA.10) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOA, &GPIO_InitStruct);
		

		
	} else if (pinspack == Pins_PB6PB7) {
		// Enable clock for GPIOB
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,ENABLE);
		//Configure USART1 Tx (P) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStruct);

		// Configure USART1 Rx (P) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
}
#endif

#ifdef USE_USART2
void USART2_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	if (pinspack == Pins_PA2PA3) {
		// Enable clock for GPIOA
		 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
		 RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE);
      //Configure USART2 Tx (PA.02) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStruct);
     //Configure USART2 Rx (PA.03) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOA, &GPIO_InitStruct);
		
	} else if (pinspack == Pins_PD5PD6) {
		// Enable clock for GPIOD
		 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD , ENABLE);
		 RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE);
      //Configure USART2 Tx (P) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOD, &GPIO_InitStruct);
     //Configure USART2 Rx (P) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOD, &GPIO_InitStruct);

	}
}
#endif

#ifdef USE_USART3
void USART3_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for USART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	if (pinspack == Pins_PB10PB11) {
		
		// Enable clock for GPIOB
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB1Periph_USART3,ENABLE);
		//Configure USART1 Tx (P) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStruct);

		// Configure USART1 Rx (P) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOB, &GPIO_InitStruct);
	} else if (pinspack == Pins_PC10PC11) {
		// Enable clock for GPIOC
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB1Periph_USART3,ENABLE);
		//Configure USART1 Tx (P) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOC, &GPIO_InitStruct);

		// Configure USART1 Rx (P) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOC, &GPIO_InitStruct);
	} else if (pinspack == Pins_PD8PD9) {
		// Enable clock for GPIOD
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB2PeriphClockCmd( RCC_APB1Periph_USART3,ENABLE);
		//Configure USART1 Tx (P) as alternate function push-pull 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOD, &GPIO_InitStruct);

		// Configure USART1 Rx (P) as input floating 
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}
#endif

#ifdef USE_UART4
void UART4_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	if (pinspack == Pins_PA0PA1) {
		// Enable clock for GPIOA
		
	} else if (pinspack == Pins_PC10PC11) {
		// Enable clock for GPIOC
		
	}
}
#endif

#ifdef USE_UART5
void UART5_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for UART5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	if (pinspack == Pins_PC12PD2) {
		
	}
}
#endif


#ifdef USE_UART7
void UART7_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for UART7
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	if (pinspack == Pins_PB8PE7) {
		// Enable clock for GPIOE
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_UART7);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_UART7);
		//                         TX           RX
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7;

		//Alternating function
		GPIO_Init(GPIOE, &GPIO_InitStruct);
	} else if (pinspack ==  Pins_PF7PF6) {
		// Enable clock for GPIOF
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

		GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_UART7);
		//                         TX           RX
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;

		//Alternating function
		GPIO_Init(GPIOF, &GPIO_InitStruct);
	}
}
#endif

#ifdef USE_UART8
void UART8_InitPins(USART_PinsPack_t pinspack) {
	//Enable clock for UART8
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);

	if (pinspack == Pins_PE1PE0) {
		// Enable clock for GPIOE
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
		//                         TX           RX
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;

		//Alternating function
		GPIO_Init(GPIOE, &GPIO_InitStruct);
	}
}
#endif

#ifdef USE_USART1
void USART1_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
		#ifdef USART1_USE_CUSTOM_IRQ
			//Call user function
			USART1_ReceiveHandler(USART1->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_USART1, USART1->DR);
		#endif
	}
}
#endif

#ifdef USE_USART2
void USART2_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
		#ifdef USART2_USE_CUSTOM_IRQ
			//Call user function
			USART2_ReceiveHandler(USART2->DR);
		#else 
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_USART2, USART2->DR);
		#endif
	}
}
#endif

#ifdef USE_USART3
void USART3_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(USART3, USART_IT_RXNE)) {
		#ifdef USART3_USE_CUSTOM_IRQ
			//Call user function
			USART3_ReceiveHandler(USART3->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_USART3, USART3->DR);
		#endif
	}
}
#endif

#ifdef USE_UART4
void UART4_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(UART4, USART_IT_RXNE)) {
		#ifdef UART4_USE_CUSTOM_IRQ
			//Call user function
			UART4_ReceiveHandler(UART4->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_UART4, UART4->DR);
		#endif
	}
}
#endif

#ifdef USE_UART5
void UART5_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(UART5, USART_IT_RXNE)) {
		#ifdef UART5_USE_CUSTOM_IRQ
			//Call user function
			UART5_ReceiveHandler(UART5->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_UART5, UART5->DR);
		#endif
	}
}
#endif


#ifdef USE_UART7
void UART7_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(UART7, USART_IT_RXNE)) {
		#ifdef UART7_USE_CUSTOM_IRQ
			//Call user function
			UART7_ReceiveHandler(UART7->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_UART7, UART7->DR);
		#endif
	}
}
#endif

#ifdef USE_UART8
void UART8_IRQHandler(void) {
	//Check if interrupt was because data is received
	if (USART_GetITStatus(UART8, USART_IT_RXNE)) {
		#ifdef UART8_USE_CUSTOM_IRQ
			//Call user function
			UART8_ReceiveHandler(UART8->DR);
		#else
			//Put received data into internal buffer
			USART_INT_InsertToBuffer(&F4_UART8, UART8->DR);
		#endif
	}
}
#endif

////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////




