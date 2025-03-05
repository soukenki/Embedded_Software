#include "stm32f10x.h"


// 初始化PWM (不复用端口)
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


// 初始化PWM (复用GPIO端口) PA0重映射到PA15
void PWM_Init_AFIO(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 开启TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 开启AFIO时钟
	// 设置重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	// 在引脚定义表中，PA15上电默认调试端口JTDI，如果要作为普通GPIO使用，需要先关闭调试端口的复用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
	
	// GPIO PA0 LED
	GPIO_InitTypeDef GPIO_InitStructure;               // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;          // 设置PA0口
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

// 初始化PWM (舵机用例，PA1，通道2) 
// 舵机要求的周期：20ms，频率：1/20ms=50Hz，占空比：0.5ms~2.5ms
// 设置PSC+1= 72，ARR+1= 20K 时 ==== CCR设置500就是0.5ms，CCR设置2500就是2.5ms
void PWM_Init_Servo(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 开启TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
	
	// GPIO PA0 LED
	GPIO_InitTypeDef GPIO_InitStructure;               // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          // 设置PA1口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);             // 用结构体参数初始化GPIO
	
	
	// 配置内部时钟
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 创建结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;                 // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1 ;  			// PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 			// 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;   				// 创建结构体
	TIM_OCStructInit(&TIM_OCInitStruct);  				// 设置默认初始值
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;      // 输出比较的模式  PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;  	// 输出比较的极性  高极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;					// 设置CCR
	
	// TIM_OC1Init(TIM2, &TIM_OCInitStruct); // 通道1初始化
	TIM_OC2Init(TIM2, &TIM_OCInitStruct); // 通道2初始化
	// TIM_OC3Init(TIM2, &TIM_OCInitStruct); // 通道3初始化
	// TIM_OC4Init(TIM2, &TIM_OCInitStruct); // 通道4初始化
	// 同一个定时器打开多个通道时，频率必须一致，占空比由各自的CCR决定（占空比各自设定）
	// 相位：由于计数器更新，所有PWM同时跳变，相位是同步的。

	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

// 设置CCR的值
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}

// 设置CCR的值
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}
