#ifndef __TEST_LED_BUZZER_H__
#define __TEST_LED_BUZZER_H__


#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

// 点亮单个LED
void testLED1();

// LED流水灯
void testLED2();

// 蜂鸣器
void testBuzzer();

#endif