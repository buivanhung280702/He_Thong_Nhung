#ifndef __DHT11_H
#define __DHT11_H 			   
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
#define DHT11_IO_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=8<<28;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=3<<28;}
//IO										   
#define	DHT11_DQ_OUT PAout(7) 
#define	DHT11_DQ_IN  PAin(7) 


////////////////////////////////////////////////////////////////////////////////// 
//IO
//#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=8<<0;}
//#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=3<<0;}

//#define	DHT11_DQ_OUT PAout(8) 
//#define	DHT11_DQ_IN  PAin(8) 
 

u8 DHT11_Init(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Check(void);
void DHT11_Rst(void);  

#endif
