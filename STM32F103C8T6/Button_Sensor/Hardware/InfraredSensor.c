#include "InfraredSensor.h"

// 用于计数
uint16_t InfraredSensor_Count = 0;


// 初始化红外传感器
// 外部中断
void InfraredSensor_Init(void)
{
	// 开启 GPIO B 和 AFIO 的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;                      // 创建结构体
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;             // IPU上拉输入 （浮空输入/IPU上拉输入/IPD下拉输入）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  			  // pin口
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 
    GPIO_Init(GPIOB, &GPIO_InitStructure);                    // 初始化
	
	// AFIO外部中断引脚配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	// EXTI配置
	EXTI_InitTypeDef EXTI_InitStructure;                     // 创建结构体
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;              // 指定要配置的中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                // 指定中断线的新状态 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      // 中断线的模式（中断模式/事件模式）
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   // 有效边沿（上升沿/下降沿/双沿）
	EXTI_Init(&EXTI_InitStructure);                          // 初始化
	
	// NVIC配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       // 优先级分组  整个工程只需要执行一次！如果在模块里分组，请确保每个模块分组都是同一个
	
	NVIC_InitTypeDef NVIC_InitStructure;                            // 创建结构体
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;            // 指定中断通道开启 /关闭
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能 /失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              // 响应优先级
	NVIC_Init(&NVIC_InitStructure);                                 // 初始化

}


// PIN B14中断函数
void EXTI15_10_IRQHandler(void)
{
	// 判断寄存器的中断标志位是否被置为1
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		// 中断执行
		// TODO..
		
		// pin14状态
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) // 高电平1 低电平0 高低电平都触发1|0
		{
			InfraredSensor_Count++;
		}
		
		// 清除 14号中断线的 中断标志位
		EXTI_ClearITPendingBit(EXTI_Line14); 
	}
	
	/*if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1|GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) // 高电平1 低电平0 高低电平都触发1|0
	{
		// 中断执行
		// TODO..
		
		InfraredSensor_Count++;
		
		// 清除 14号中断线的 中断标志位
		EXTI_ClearITPendingBit(EXTI_Line14); 
	}*/
	
}

// 获取Count计数
uint16_t InfraredSensor_Get(void)
{
	return InfraredSensor_Count;
}


