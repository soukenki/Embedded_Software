#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

// 初始化LED
void LED_Init(void);

// 点亮指定IO口的LED  例：PA1 num传参1
void LEDSet_ON(uint8_t num);

// 熄灭指定IO口的LED  例：PA2 num传参2
void LEDSet_OFF(uint8_t num);

// 读取当前端口输出状态，实现电平翻转 
void LEDTurn(uint8_t num);

#endif
