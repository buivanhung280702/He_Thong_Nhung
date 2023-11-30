#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "i2c_lcd.h"
#include "i2c.h"
#include "ds1307.h"
#include "i2c_ds1307.h"
#include <stdio.h>

uint8_t D, d, M, y, h, m, s;
char buf[4];

int main(void)
{
	
	I2C_LCD_Init();
	
	// Initialize DS1307
	ds1307_init();
	
	// Set initial date and time 
	ds1307_set_calendar_date(DS1307_WEDNESDAY, 9, 3, 16);
	ds1307_set_time_24(10, 10, 30);
	
	while (1)
	{
		// Get date and time
		ds1307_get_calendar_date(&D, &d, &M, &y);
		ds1307_get_time_24(&h, &m, &s);
		
		// Display date and time to LCD
		I2C_LCD_Clear();
		
		sprintf(buf, (d <= 9) ? "0%d" : "%d", d);
		I2C_LCD_Puts(buf);
		I2C_LCD_Puts("/");
		sprintf(buf, (M <= 9) ? "0%d" : "%d", M);
		I2C_LCD_Puts(buf);
		I2C_LCD_Puts("/");
		sprintf(buf, "20%d", y);
		I2C_LCD_Puts(buf);
		
		I2C_LCD_NewLine();
		sprintf(buf, (h <= 9) ? "0%d" : "%d", h);
		I2C_LCD_Puts(buf);
		I2C_LCD_Puts(":");
		sprintf(buf, (m <= 9) ? "0%d" : "%d", m);
		I2C_LCD_Puts(buf);
		I2C_LCD_Puts(":");
		sprintf(buf, (s <= 9) ? "0%d" : "%d", s);
		I2C_LCD_Puts(buf);
		
		delay_ms(1000);
	}
}
