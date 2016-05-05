#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include <stdio.h>
void UsartConfig(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
