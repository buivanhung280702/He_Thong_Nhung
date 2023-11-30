#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"

void My_I2C_Init(void);
uint8_t I2C_Write(uint8_t Address, uint8_t *pData, uint8_t length);
uint8_t I2C_Read(uint8_t Address, uint8_t *pData, uint8_t length);

#endif
