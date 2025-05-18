#ifndef __TIMER_H__
#define __TIMER_H__

// 初始化定时器(内部时钟)
void InternalTimer_Init(void);

// 初始化定时器(外部时钟)
void ExternalTimer_Init(void);

// 获取预分频值
uint16_t Timer_GetCounter(void);

#endif
