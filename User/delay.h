#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h" 

void SysTick_Init(void);
void delay_us(__IO u32 nTime);
#define delay_ms(x) delay_us(100*x)	 //µ¥Î»ms
void SysTick_Handler(void);

#endif





























