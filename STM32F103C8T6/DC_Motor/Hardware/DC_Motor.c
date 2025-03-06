#include "DC_Motor.h"

// 初始化直流电机
void DC_Motor_Init()
{
	// 初始化GPIO （电机方向控制）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;   // 设置PA4和PA5口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 50MHz

	GPIO_Init(GPIOA, &GPIO_InitStructure);   // 初始化GPIO
	
	// 初始化电机的PWM
	PWM_Init_DC_Motor();  
}

// 设置速度
void DC_Motor_SetSpeed(int8_t speed)
{
	// 正转
	if (speed >= 0)
	{
		// 设置高低各一个的电平（控制正反转）
		GPIO_SetBits(GPIOA, GPIO_Pin_4); 
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare3(speed);
	}
	else // 反转
	{
		// 设置高低各一个的电平（控制正反转）
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5); 
		PWM_SetCompare3(-(speed));
	}
}
