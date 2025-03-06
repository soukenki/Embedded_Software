#ifndef __TEST_LED_BUZZER_H__
#define __TEST_LED_BUZZER_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Button.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"

// 按钮控制LED
void testButton(void);


// 测试蜂鸣器
void testBuzzer(void);

// 测试光传感
void testLightSensor(void);

// 测试OLED
void testOLED(void);

#endif
