// 新建工程模板 寄存器版

#include "my_stm32f4xx.h"

#include "my_stm32f4xx_gpio.h"
#include "bsp_led.h"

// 延时
void LED_Delay(unsigned int count)
{
	for (; count!= 0; count--);
}

// 初始化 寄存器版
void LED_init_GPIOH10_reg(void)
{
	// 开启GPIOH时钟
	RCC_AHB1ENR |= (1 << 7);
	
	// GPIOH10 MODER寄存器的第10位清空
	GPIOH_MODER &= ~(0x03 << (2 * 10));
	// 配置PH10口为输出模式
	GPIOH_MODER |= (1 << (2 * 10));
	
	// GPIOH OTYPER寄存器10清空
	GPIOH_OTYPER &= ~(1 << (1 * 10));
	// 0b 推挽模式
	GPIOH_OTYPER |= (0 << (1 * 10));
	
	// GPIOH OSPEEDR寄存器10清空
	GPIOH_OSPEEDR &= ~(0x03 << (2 * 10));
	// 0b 速率2MHz
	GPIOH_OSPEEDR |= (0 << (2 * 10));
	
	// GPIOH PUPDR寄存器10清空
	GPIOH_PUPDR &= ~(0x03 << (2 * 10));
	// 01b 上拉模式
	GPIOH_PUPDR |= (1 << (2 * 10));
	
}

// 初始化 寄存器的结构体版
void LED_init_GPIOH10_str(void)
{
	// 开启GPIOH时钟
	RCC_AHB1ENR |= (1 << 7);
	
	// GPIOH10 MODER寄存器的第10位清空
	GPIOH->MODER &= ~(0x03 << (2 * 10));
	// 配置PH10口为输出模式
	GPIOH->MODER |= (1 << (2 * 10));
	
	// GPIOH OTYPER寄存器10清空
	GPIOH->OTYPER &= ~(1 << (1 * 10));
	// 0b 推挽模式
	GPIOH->OTYPER |= (0 << (1 * 10));
	
	// GPIOH OSPEEDR寄存器10清空
	GPIOH->OSPEEDR &= ~(0x03 << (2 * 10));
	// 0b 速率2MHz
	GPIOH->OSPEEDR |= (0 << (2 * 10));
	
	// GPIOH PUPDR寄存器10清空
	GPIOH->PUPDR &= ~(0x03 << (2 * 10));
	// 01b 上拉模式
	GPIOH->PUPDR |= (1 << (2 * 10));
}

// 点亮/灭灯
void LED_GPIOH10_(unsigned int num)
{
	if (num)
	{
		// PH10 ODR输出低电平
		GPIOH_ODR &= ~(1 << 10); 
		
		// GPIOH BSRR寄存器的 BR10置1，使引脚输出低电平
		//GPIOH_BSRR |= (1 << 16 << 10);
	}
	else
	{
		// PH10 ODR输出高电平
		GPIOH_ODR |= (1 << 10); 
		
		// GPIOH BSRR寄存器的 BS10置1，使引脚输出高电平
		//GPIOH_BSRR |= (1 << 10);
	}
}



int main(void)
{
	// LED_init_GPIOH10_reg();
	// LED_init_GPIOH10_str();
	LED_GPIO_Config();
	
	while (1)
	{
		
		//LED_GPIOH10_(1);
		GPIO_SetBits(GPIOH, 10); 
		LED_Delay(0xFFFFF);
	
		//LED_GPIOH10_(0);
		GPIO_ResetBits(GPIOH, 10);
		LED_Delay(0xFFFFF);
	}
		
}
