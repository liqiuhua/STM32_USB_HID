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

/// ����USART1�����ж�
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


/// �ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

/// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
