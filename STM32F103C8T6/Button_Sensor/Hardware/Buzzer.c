#include "Buzzer.h"

// 初始化蜂鸣器
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}


// 开蜂鸣器
void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12); // 响
}


// 关蜂鸣器
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);  // 不响
}

// 读取当前端口输出状态，实现电平翻转 
void BuzzerTurn(void)
{
	if (0 == GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12))  
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);  // 如果低电平，就熄灭
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // 点亮
	}
}