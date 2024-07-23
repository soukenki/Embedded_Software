#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "UART.h"



int main(void)  
{
	OLED_Init();
	
	UART_Init();
	
	UART_SendByte(0x41);   // 写字节
	
	uint8_t arr[] = {0x42, 0x43, 0x44};
	UART_SendArray(arr, 3);  // 写数组
	
	UART_SendString("\r\n hello! \r\n");   // 写字符串
	
	UART_SendNumber(12345, 5);  // 写数字
	
	
	// 使用printf之类的函数，需要在设置中勾选 Target -> Use MicroLIB 
	printf("\r\nnum = %d\r\n", 111);   // printf重定向到MCU
	
	char string[100];
	sprintf(string, "\r\nnum = %d\r\n", 111);  // 重定向
	UART_SendString(string);
	
	UART_Printf("\r\nnum = %d\r\n", 111);     // 可变参数的printf
	
	// UART_Printf("你好！");  // 需要设置编码为GB2312
	
	uint8_t row = 1;
	uint8_t col = 1;
	while(1)
	{
		//if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)  // 轮询查是否有数据可读
		//{
		//	uint8_t RxData = USART_ReceiveData(USART1);  // 接收数据
		//	OLED_ShowHexNum(1, 1, RxData, 2);
		//}
		
		
		if (UART_GetRxFlag() == 1)   // 轮询读取中断保存的数据
		{
			uint8_t RxData = UART_GetRxData();  // 接收数据
			UART_SendByte(RxData);            // 把接收到的数据发回去
			// 打印到OLED
			if (col < 16)
			{
				OLED_ShowHexNum(row, col, RxData, 2);
				col+=2;
				if (col >= 16 && row < 4)
				{
					row++;
					col = 1;
				}
			}
			else
			{
				OLED_Clear();
				col = 1;
				row = 1;
				OLED_ShowHexNum(row, col, RxData, 2);
				col+=2;
			}
		}
	}
}

