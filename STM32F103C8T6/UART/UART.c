#include "UART.h"


// 全局变量
uint8_t rx_data = 0;
uint8_t rx_flag = 0;

// 初始化UART
void UART_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 写初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 读初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;   			// 波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控（用/不用）
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;       		// 模式（读/写）
	USART_InitStructure.USART_Parity = USART_Parity_No;   		// 校验位（奇/偶/无）
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		// 停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 数据位数
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   // 开启RXNE标志位到NVIC的输出（RXNE置1时，申请中断）
	
	// 中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;      		// 中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// 使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 响应优先级
	
	NVIC_Init(&NVIC_InitStructure);
}

// 写一个字节
void UART_SendByte(uint8_t byte)
{
	USART_SendData(USART1, byte); // 写数据
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);  // 不为1循环等待（DR的数据移动到移位寄存器，结束置1）
}

// 写一个数组
void UART_SendArray(uint8_t *arr, uint16_t len)
{
	for (uint8_t i = 0; i < len; i++)
	{
		UART_SendByte(arr[i]);
	}
}

// 写一个字符串
void UART_SendString(char *str)
{
	for (uint8_t i = 0; str[i] != 0; i++)
	{
		UART_SendByte(str[i]);
	}
}

// 次方函数
uint32_t UART_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	while (y--)
	{
		result *= x;
	}
	return result;
}

// 写数字
void UART_SendNumber(uint32_t num, uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
	{
		UART_SendByte((num / UART_Pow(10, len - i - 1) % 10) + '0');
	}
}


// 重写fputc函数 （用于输出重定向到MCU，printf底层是fputc）
int fputc(int ch, FILE *f)
{
	UART_SendByte(ch);
	return ch;
}

// 可变参数的printf
void UART_Printf(char *format, ...)
{
	char str[100];
	va_list arg;       // 创建list
	va_start(arg, format);   // 把format中的数据，插入list链表
	vsprintf(str, format, arg);  // 把链表数据输出到str数组（buf）
	va_end(arg);        // 释放list
	UART_SendString(str);   // 使用串口读
}

// 获取rx flag
uint8_t UART_GetRxFlag(void)
{
	if (rx_flag == 1)
	{
		rx_flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

// 获取rx data
uint8_t UART_GetRxData(void)
{
	return rx_data;
}

// 中断函数
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)  // 查询RXNE标志位是否置1
	{
		rx_data = USART_ReceiveData(USART1);
		rx_flag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

