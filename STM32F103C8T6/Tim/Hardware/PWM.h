#ifndef __PWM_H__
#define __PWM_H__

#include "stdint.h"

// 初始化PWM
extern void PWM_Init(void);

// 初始化PWM (复用GPIO端口) PA0重映射到PA15
extern void PWM_Init_AFIO(void);

// 初始化PWM (舵机用例，PA1，通道2) 
// 舵机要求的周期：20ms，频率：1/20ms=50Hz，占空比：0.5ms~2.5ms
// 设置PSC+1= 72，ARR+1= 20K 时 ==== CCR设置500就是0.5ms，CCR设置2500就是2.5ms
extern void PWM_Init_Servo(void);

// 设置CCR的值 （通道1）
extern void PWM_SetCompare1(uint16_t Compare);

// 设置CCR的值（通道2）
extern void PWM_SetCompare2(uint16_t Compare);

#endif
