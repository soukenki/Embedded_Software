#include "Test_Timer.h"

extern uint16_t num;

/**
  * @brief  初始化定时器(内部时钟)
  * @param  无
  * @retval 无
  */
void InternalTimer_Init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 配置内部时钟
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 创建结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1; // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1 ; // PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 因为有缓冲(影子)寄存器存在，所以第一次开启立马刷新一次更新事件
	// 是为了让值立即起作用，让预分频器的值有效。
	// 副作用是导致马上触发中断，置1中断标志位，所以初始化一结束立即进入中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      // 清除中断标志位
	
	// 配置中断输出控制
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 开启 更新中断 到NVIC的通道
	
	// 配置NVIC优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    // 优先级分组2
	
	// 配置NVIC
	NVIC_InitTypeDef NVIC_InitStructure;                            // 创建结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 // 定时器2的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能 /失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              // 响应优先级
	NVIC_Init(&NVIC_InitStructure);                                 // 初始化

	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

// 初始化定时器(外部时钟)
void ExternalTimer_Init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 外部时钟的GPIO
	
	GPIO_InitTypeDef GPIO_InitStructure;                 // 初始化GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        // 上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            // pin0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// 配置ETR引脚的外部时钟
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F); 
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 创建结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 给滤波器的频率，用（1/2/4）分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式（向上/向下/3种中央 计数）
	// 定时频率 = 72M / (PSC + 1) / (ARR + 1) =  10K / 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1; // ARR自动重装器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1 ; // PSC预分频器的值  0~65535
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器的值（只有高级定时器才有，不用时，设置0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 因为有缓冲(影子)寄存器存在，所以第一次开启立马刷新一次更新事件
	// 是为了让值立即起作用，让预分频器的值有效。
	// 副作用是导致马上触发中断，置1中断标志位，所以初始化一结束立即进入中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);      // 清除中断标志位
	
	// 配置中断输出控制
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 开启 更新中断 到NVIC的通道
	
	// 配置NVIC优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    // 优先级分组2
	
	// 配置NVIC
	NVIC_InitTypeDef NVIC_InitStructure;                            // 创建结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 // 定时器2的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能 /失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              // 响应优先级
	NVIC_Init(&NVIC_InitStructure);                                 // 初始化

	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

// 获取预分频值
uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}


// TIM2的中断函数（当定时器产生更新中断时，自动执行）
void TIM2_IRQHandler(void)
{
	// 检查中断标志位
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		// TODO
		num++;
		// 清除中断标记位
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
