#ifndef __Buzzer_H__
#define __Buzzer_H__

#include "stm32f10x.h"                  // Device header

// 初始化蜂鸣器
void Buzzer_Init(void);


// 开蜂鸣器
void Buzzer_ON(void);

// 关蜂鸣器
void Buzzer_OFF(void);

// 读取当前端口输出状态，实现电平翻转 
void BuzzerTurn(void);

#endif
