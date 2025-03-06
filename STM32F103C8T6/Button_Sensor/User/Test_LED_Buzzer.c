#include "Test_LED_Buzzer.h"

// 点亮单个LED
void testLED1()
{
	GPIO_InitTypeDef GPIO_InitStructure;    // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽模式
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // 开漏模式
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   // 设置PA0和PA1口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  // 设置PA的全部口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 50MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 打开使能GPIOA时钟
	GPIO_Init(GPIOA, &GPIO_InitStructure);   // 用结构体参数初始化GPIO
	
	while (1)
	{
		//GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);  // 点亮PA0和PA1
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // 点亮PA0
		Delay_ms(500);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_0);    // 熄灭PA0
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);   // 点亮
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);  	 // 熄灭
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)0);   // 点亮
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)1);  	 // 熄灭
		Delay_ms(500);
	}

}

// LED流水灯
void testLED2()
{
	GPIO_InitTypeDef GPIO_InitStructure;    // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽模式
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // 开漏模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;  // 设置PA的全部口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 50MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 打开使能GPIOA时钟
	GPIO_Init(GPIOA, &GPIO_InitStructure);   // 用结构体参数初始化GPIO
	
	while (1)
	{
		// LED流水点亮
		for (int i = 0; i < 8; ++i)
		{
			GPIO_Write(GPIOA, ~(0x0001 << i));  // 0000 0000 0000 0001 ~ 0000 0000 1000 0000
			Delay_ms(500);                      
		}
	}
}

// 蜂鸣器
void testBuzzer()
{
	GPIO_InitTypeDef GPIO_InitStructure;    // 创建结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽模式
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // 开漏模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // 设置PA的全部口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 50MHz
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   // 打开使能GPIOB时钟
	GPIO_Init(GPIOB, &GPIO_InitStructure);   // 用结构体参数初始化GPIOB
	
	while (1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // PA12置低电平0
		Delay_ms(100);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_12);    // PA12置高电平1
		Delay_ms(100);
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // PA12置低电平0
		Delay_ms(100);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_12);    // PA12置高电平1
		Delay_ms(700);
	}
}
