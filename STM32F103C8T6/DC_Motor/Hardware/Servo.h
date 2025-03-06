#ifndef __SERVO_H__
#define __SERVO_H__

#include "PWM.h"

// 初始化舵机
void Servo_Init(void);

// 设置角度 0，90，180
void Servo_SetAngle(float Angle);


#endif
