#include "LED.h"


// 初始化LED
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
}


// 点亮指定IO口的LED  例：PA1 num传参1
void LEDSet_ON(uint8_t num)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 << num);  // 点亮
}


// 熄灭指定IO口的LED  例：PA2 num传参2
void LEDSet_OFF(uint8_t num)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0 << num);  // 熄灭
}

// 读取当前端口输出状态，实现电平翻转 
void LEDTurn(uint8_t num)
{
	if (0 == GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0 << num))  
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0 << num);  // 如果低电平，就熄灭
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 << num);  // 点亮
	}
}

