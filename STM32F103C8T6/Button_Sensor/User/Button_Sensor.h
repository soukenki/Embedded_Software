#ifndef __Button_Sensor_H__
#define __Button_Sensor_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Button.h"
#include "Buzzer.h"
#include "LightSensor.h"

// 测试按钮控制LED
void testButton(void);


// 测试蜂鸣器
void testBuzzer(void);

// 测试光传感
void testLightSensor();

#endif
