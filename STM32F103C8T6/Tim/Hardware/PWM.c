#include "stm32f10x.h"


// 初始化PWM
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 开启TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
	
	// GPIO PA0 LED
	GPIO_InitTypeDef GPIO_InitStructure;               // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          // 设置PA0口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);             // 用结构体参数初始化GPIO
	
	
	// 配置内部时钟
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 创建结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1 ;  			// PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 			// 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;   				// 创建结构体
	TIM_OCStructInit(&TIM_OCInitStruct);  				// 设置默认初始值
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;      // 输出比较的模式  PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;  	// 输出比较的极性  高极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;					// 设置CCR
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);

	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

// 设置CCR的值
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}

