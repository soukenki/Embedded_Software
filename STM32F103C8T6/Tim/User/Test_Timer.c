#include "Test_Timer.h"

uint16_t num = 0;

// 测试内部定时器
void testInternalTimer(void)
{
	OLED_Init();
	InternalTimer_Init();
	
	OLED_ShowString(1, 1, "num:");
	OLED_ShowString(2, 1, "cnt:");
	
	while (1)
	{
		OLED_ShowNum(1, 5, num, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);   // 一直循环0->自动重装值
		
	}
}


// 测试外部时钟
void testExternalTimer(void)
{
	OLED_Init();
	ExternalTimer_Init();
	
	OLED_ShowString(1, 1, "num:");
	OLED_ShowString(2, 1, "cnt:");
	while (1)
	{
		OLED_ShowNum(1, 5, num, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);   // 一直循环0->自动重装值
		
	}
}

// 测试PWM控制LED呼吸灯(渐变)
void testControlLED_PWM(void)
{
	OLED_Init();
	PWM_Init();  // 初始化PWM
	
	OLED_ShowString(1, 1, "testControlLED_PWM");
	int i = 0;
	while (1)
	{
		for (i = 0; i < 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		
		for (i = 0; i < 100; i++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
	}
}


