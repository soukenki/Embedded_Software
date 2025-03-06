#ifndef __Button_H__
#define __Button_H__

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

// 初始化按钮
void Button_Init(void);

// 检测按钮
uint8_t Button_GetNum(void);

#endif

