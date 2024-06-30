// 自定义寄存器映射代码

#ifndef __MY_STM32F4XX_H__
#define __MY_STM32F4XX_H__


// 片上外设基地址
#define PERIPH_BASE           ((unsigned int)0x40000000)                          

// 总线基地址
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)	

// GPIO外设基地址
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00)
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000)

// GPIOH寄存器地址,强制转换成指针 
#define GPIOH_MODER				*(unsigned int*)(GPIOH_BASE + 0x00)
#define GPIOH_OTYPER			*(unsigned int*)(GPIOH_BASE + 0x04)
#define GPIOH_OSPEEDR			*(unsigned int*)(GPIOH_BASE + 0x08)
#define GPIOH_PUPDR				*(unsigned int*)(GPIOH_BASE + 0x0C)
#define GPIOH_IDR				*(unsigned int*)(GPIOH_BASE + 0x10)
#define GPIOH_ODR				*(unsigned int*)(GPIOH_BASE + 0x14)
#define GPIOH_BSRR				*(unsigned int*)(GPIOH_BASE + 0x18)
#define GPIOH_LCKR				*(unsigned int*)(GPIOH_BASE + 0x1C)
#define GPIOH_AFRL				*(unsigned int*)(GPIOH_BASE + 0x20)
#define GPIOH_AFRH				*(unsigned int*)(GPIOH_BASE + 0x24)

// RCC外设基地址
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)

// RCC的AHB1时钟使能寄存器地址,强制转换成指针
#define RCC_AHB1ENR				*(unsigned int*)(RCC_BASE + 0x30)

// 使用结构体定义寄存器
#define GPIOH 				  ((GPIO_TypeDef *)GPIOH_BASE)
#define GPIOA 				  ((GPIO_TypeDef *)GPIOA_BASE)

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint16_t BSRRL;
	uint16_t BSRRH;
	uint32_t LCKR;
	uint32_t AFR[2];
}GPIO_TypeDef;





#endif
