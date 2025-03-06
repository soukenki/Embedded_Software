#ifndef __INFRARED_SENSOR_H__
#define __INFRARED_SENSOR_H__

#include "stm32f10x.h"                  // Device header

// 初始化红外传感器
// 外部中断
void InfraredSensor_Init(void);

// 获取Count计数
uint16_t InfraredSensor_Get(void);

#endif
