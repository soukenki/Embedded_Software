#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__

#include "stm32f10x.h"                  // Device header
#include "PWM.h"

// 初始化直流电机
extern void DC_Motor_Init(void);

// 设置速度
extern void DC_Motor_SetSpeed(int8_t speed);


#endif
