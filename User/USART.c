#include "USART.H"

void UsartConfig(void)
{
	//the usart1 gpio config
	GPIO_InitTypeDef Usart_GPIO;
	USART_InitTypeDef Usart;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	Usart_GPIO.GPIO_Pin=GPIO_Pin_9;
	Usart_GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
	Usart_GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Usart_GPIO);
	
	Usart_GPIO.GPIO_Pin=GPIO_Pin_10;
	Usart_GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	Usart_GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Usart_GPIO);
	
	//usart1 mode config
	Usart.USART_BaudRate=115200;
	Usart.USART_WordLength=USART_WordLength_8b;
	Usart.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	Usart.USART_Parity=USART_Parity_No;
	Usart.USART_StopBits=USART_StopBits_1;
	Usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_Init(USART1, &Usart);
	USART_Cmd(USART1, ENABLE);
	
}

/// 配置USART1接收中断
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/// 重定向c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
