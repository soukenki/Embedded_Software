#ifndef __TEST_BUTTON_SENSOR_H__
#define __TEST_BUTTON_SENSOR_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Button.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "InfraredSensor.h"

// 按钮控制LED
void testButton(void);


// 测试蜂鸣器
void testBuzzer(void);

// 测试光传感
void testLightSensor();

// 测试红外传感器
void testInfraredSensor();

#endif
