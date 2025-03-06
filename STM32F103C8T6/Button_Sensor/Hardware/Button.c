#include "Button.h"

void Button_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Button_GetNum(void)
{
	uint8_t ButtonNum = 0;
	
	if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))  // 按下按钮
	{
		// 消抖
		Delay_ms(20);
		while (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)) ;
		Delay_ms(20);
		ButtonNum = 1;
	}
	
	if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))  // 按下按钮
	{
		// 消抖
		Delay_ms(20);
		while (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) ;
		Delay_ms(20);
		ButtonNum = 2;
	}
	return ButtonNum;
}

