#ifndef __AD_H__
#define __AD_H__

#include "stm32f10x.h"                  // Device header


// 单通道
void AD_Init_One(void);

// 多通道
void AD_Init_Multiple(void);

// 启动转换 获取结果 （单通道）
uint16_t AD_GetValue_One(void);

// 启动转换 获取结果 （多通道）
uint16_t AD_GetValue_Multiple(uint8_t ADC_Channel);


#endif
