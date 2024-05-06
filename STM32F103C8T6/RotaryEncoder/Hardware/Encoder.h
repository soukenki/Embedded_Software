#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "stm32f10x.h"

// 初始化旋转编码器
// 外部中断
void Encoder_Init(void);

// 获取计数值
int16_t Encoder_Get(void);

#endif
