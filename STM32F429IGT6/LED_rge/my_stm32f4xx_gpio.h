// 自定义GPIO寄存器映射代码

#ifndef __MY_STM32F4XX_GPIO_H__
#define __MY_STM32F4XX_GPIO_H__

#include "my_stm32f4xx.h"

#define GPIO_Pin_0			((uint16_t)(0x0001))
#define GPIO_Pin_1			((uint16_t)(0x0002))
#define GPIO_Pin_2			((uint16_t)(0x0004))
#define GPIO_Pin_3			((uint16_t)(0x0008))

#define GPIO_Pin_4			((uint16_t)(0x0010))
#define GPIO_Pin_5			((uint16_t)(0x0020))
#define GPIO_Pin_6			((uint16_t)(0x0040))
#define GPIO_Pin_7			((uint16_t)(0x0080))

#define GPIO_Pin_8			((uint16_t)(0x0100))
#define GPIO_Pin_9			((uint16_t)(0x0200))
#define GPIO_Pin_10			((uint16_t)(0x0400))
#define GPIO_Pin_11			((uint16_t)(0x0800))

#define GPIO_Pin_12			((uint16_t)(0x1000))
#define GPIO_Pin_13			((uint16_t)(0x2000))
#define GPIO_Pin_14			((uint16_t)(0x4000))
#define GPIO_Pin_15			((uint16_t)(0x8000))
#define GPIO_Pin_ALL		((uint16_t)(0xFFFF))



typedef struct
{
	uint32_t GPIO_Pin;     // pin口
	uint8_t GPIO_Mode;     // 模式  	 @GPIOMode_TypeDef
	uint8_t GPIO_OType;    // 推挽/开漏   @GPIOOType_TypeDef
	uint8_t GPIO_Speed;    // 速率 		 @GPIOSpeed_TypeDef
	uint8_t GPIO_PuPd;     // 上拉/下拉   @GPIOPuPd_TypeDef
}GPIO_IninTyeDef;

typedef enum
{
	GPIO_Mode_IN  = 0x00,	// 输入
	GPIO_Mode_OUT = 0x01,	// 输出
	GPIO_Mode_AF  = 0x02,	// 复用
	GPIO_Mode_AN  = 0x03	// 模拟
}GPIOMode_TypeDef;


typedef enum
{
	GPIO_OType_PP  = 0x00,		// 推挽输出
	GPIO_OType_OD = 0x01		// 开漏输出
}GPIOOType_TypeDef;

typedef enum
{
	GPIO_Speed_2MHz    = 0x00,	
	GPIO_Speed_25MHz   = 0x01,	
	GPIO_Speed_50MHz   = 0x02,	
	GPIO_Speed_100MHz  = 0x03	
}GPIOSpeed_TypeDef;

typedef enum
{
	GPIO_PuPd_NOPULL  = 0x00,	// 浮空
	GPIO_PuPd_UP 	  = 0x01,	// 上拉
	GPIO_PuPd_DOWN    = 0x02,	// 下拉
}GPIOPuPd_TypeDef;


/* 设置引脚 高电平
 * GPIOx：GPIO端口号     GPIO_Pin：端口的引脚号
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

// 复位引脚 低电平
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

// 初始化
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_IninTyeDef *GPIO_InitStruct);

#endif
