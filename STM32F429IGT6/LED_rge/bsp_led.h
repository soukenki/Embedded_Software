#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "my_stm32f4xx.h"
#include "my_stm32f4xx_gpio.h"

#define LED_R_GPIO_PIN 		GPIO_Pin_10
#define LED_R_GPIO_PORT 	GPIOH

#define LED_G_GPIO_PIN 		GPIO_Pin_11
#define LED_G_GPIO_PORT 	GPIOH

#define LED_B_GPIO_PIN 		GPIO_Pin_12
#define LED_B_GPIO_PORT 	GPIOH

// 封装的结构体 初始化
void LED_GPIO_Config(void);

#endif
