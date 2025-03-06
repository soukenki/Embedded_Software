#ifndef __LightSensor_H__
#define __LightSensor_H__

#include "stm32f10x.h"                  // Device header

// 初始化光传感
void LightSensor_Init(void);

// 读取端口
uint8_t LightSensor_Get(void);

#endif
