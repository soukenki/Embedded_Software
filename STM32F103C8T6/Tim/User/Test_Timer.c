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
