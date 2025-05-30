// 定时器输入捕获
#ifndef __IC_H__
#define __IC_H__

#include "stm32f10x.h"

// 初始化输入捕获
extern void IC_Init(void);

// 初始化输入捕获_PWMI模式
extern void IC_Init_PWMI(void);

// 获取频率
extern uint32_t IC_GetFreq(void);

// 获取占空比
extern uint32_t IC_GetDuty(void);


#endif
