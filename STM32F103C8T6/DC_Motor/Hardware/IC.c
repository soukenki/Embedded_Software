#include "IC.h"

// 测频率的范围：
// 下限：
//  因为标准频率为 1MHz，计数器最大计数为65535，所以所测量的最低频率为 1M/65535，这个值大概是 15Hz。
//  如果信号频率再低，计数器就会溢出。如果需要再降低频率，就要把预分频再加大。
// 上限：
//  最大频率并没有一个明显的界限，随着待测频率增大，误差也会增大。
//  如果一定要有频率上限，就是标准频率 1MHz。（误差会很大）

// 初始化输入捕获
void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 开启TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      // 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;          // 设置PA6口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// 配置内部时钟
	TIM_InternalClockConfig(TIM3);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1 ;  			// PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 			// 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct;   						// 创建结构体
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;      			// 通道1
	TIM_ICInitStruct.TIM_ICFilter = 0xF;  						// 滤波，滤波大小可选：0x0~0xF
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;  	// 上升沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;			// 不分频
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;// 直流通道输入
	TIM_ICInit(TIM3, &TIM_ICInitStruct);

	// 触发源选择
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1); 
	
	// 配置从模式为Reset
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

	// 启动定时器
	TIM_Cmd(TIM3, ENABLE);	
}

// 初始化输入捕获_PWMI模式
void IC_Init_PWMI(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 开启TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
	
	// GPIO PA0 LED
	GPIO_InitTypeDef GPIO_InitStructure;               // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      // 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;          // 设置PA6口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// 配置内部时钟
	TIM_InternalClockConfig(TIM3);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 创建结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1 ;  			// PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 			// 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct;   						// 创建结构体
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;      			// 通道1
	TIM_ICInitStruct.TIM_ICFilter = 0xF;  						// 滤波，滤波大小可选：0x0~0xF
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;  	// 上升沿触发
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;			// 不分频
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;// 直连通道输入
	// TIM_ICInit(TIM3, &TIM_ICInitStruct);
	// TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;      			  // 通道2
	// TIM_ICInitStruct.TIM_ICFilter = 0xF;  						  // 滤波，滤波大小可选：0x0~0xF
	// TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;  	  // 下降沿触发
	// TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;			  // 不分频
	// TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;// 交叉通道输入
	// TIM_ICInit(TIM3, &TIM_ICInitStruct);
	
	TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);   // 同上方注释内的内容，自动配置相反的配值，实现PWMI


	// 触发源选择
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1); 
	
	// 配置从模式为Reset
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

	// 启动定时器
	TIM_Cmd(TIM3, ENABLE);	
}

// 获取频率
uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1); // +1只是为了数据看起来更完整，可以不加
}

// 获取占空比
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1); // +1只是为了数据看起来更完整，可以不加
}

