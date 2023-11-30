#include <stm32f10x.h>
#include "I2C.h"
#include "delay.h"

#define SDA_0 GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define SDA_1 GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define SCL_0 GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define SCL_1 GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define SDA_VAL (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))

void i2c_init(void)
{
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpioInit);
	
	SDA_1;
	SCL_1;
}

void i2c_start(void)
{
	
	SCL_1;
	delay_us(3);
	SDA_1;
	delay_us(3);
	SDA_0;
	delay_us(3);
	SCL_0;
	delay_us(3);
}

void i2c_stop(void)
{
	
	SDA_0;
	delay_us(3);
	SCL_1;
	delay_us(3);
	SDA_1;
	delay_us(3);
}

uint8_t i2c_write(uint8_t u8Data)
{
	uint8_t i;
	uint8_t u8Ret;
	
	for (i = 0; i < 8; ++i) {
		if (u8Data & 0x80) {
			SDA_1;
		} else {
			SDA_0;
		}
		delay_us(3);
		SCL_1;
		delay_us(5);
		SCL_0;
		delay_us(2);
		u8Data <<= 1;
	}
	
	SDA_1;
	delay_us(3);
	SCL_1;
	delay_us(3);
	if (SDA_VAL) {
		u8Ret = 0;
	} else {
		u8Ret = 1;
	}
	delay_us(2);
	SCL_0;
	delay_us(5);
	
	return u8Ret;
}

uint8_t i2c_read(uint8_t u8Ack)
{
	uint8_t i;
	uint8_t u8Ret;
	
	SDA_1;
	delay_us(3);
	
	for (i = 0; i < 8; ++i) {
		u8Ret <<= 1;
		SCL_1;
		delay_us(3);
		if (SDA_VAL) {
			u8Ret |= 0x01;
		}
		delay_us(2);
		SCL_0;
		delay_us(5);
	}
	
	if (u8Ack) {
		SDA_0;
	} else {
		SDA_1;
	}
	delay_us(3);
	
	SCL_1;
	delay_us(5);
	SCL_0;
	delay_us(5);
	
	return u8Ret;
}

void My_I2C_Init(void)
{
	i2c_init();
}

uint8_t I2C_Write(uint8_t Address, uint8_t *pData, uint8_t length)
{
	uint8_t i;
	
	i2c_start();
	if (i2c_write(Address) == 0) {
		i2c_stop();
		return 0;
	}
	for (i = 0; i < length; ++i) {
		if (i2c_write(pData[i]) == 0) {
			i2c_stop();
			return 0;
		}
	}
	i2c_stop();
	
	return 1;
}

uint8_t I2C_Read(uint8_t Address, uint8_t *pData, uint8_t length)
{
	uint8_t i;
	
	i2c_start();
	
	if (i2c_write(Address) == 0) {
		i2c_stop();
		return 0;
	}
	
	for (i = 0; i < length - 1; ++i) {
		pData[i] = i2c_read(1);
	}
	pData[i] = i2c_read(0);
	
	i2c_stop();
	
	return 1;
}
