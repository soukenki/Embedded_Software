#ifndef __TEST_TIMER_H__
#define __TEST_TIMER_H__

#include "stm32f10x.h"
#include "stdbool.h"
#include "Delay.h"
#include "OLED.h"
#include "Button.h"
#include "Timer.h"
#include "PWM.h"
#include "Servo.h"
#include "DC_Motor.h"
#include "IC.h"

// 测试内部定时器
extern void testInternalTimer(void);

// 测试外部时钟
extern void testExternalTimer(void);

// 测试PWM控制LED呼吸灯(渐变)
extern void testControlLED_PWM(void);

// 测试PWM控制舵机
extern void testControlServo_PWM(void);

// 测试按键控制舵机
extern void testControlServo_Key(void);

// 测试PWM控制直流电机
extern void testControlDC_Motor_PWM(void);

// 测试按键控制直流电机
extern void testControlDC_Motor_Key(void);

// 输入捕获测频率
extern void testPWMFreq(void);

// PWMI输入捕获测频率+占空比
extern void testPWMIFreqDuty(void);

#endif
