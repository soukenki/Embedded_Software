#include "testOLED.h"



// 测试OLED
void testOLED(void)
{
	OLED_Init();
	
	OLED_ShowChar(1, 1, 'K');
	OLED_ShowString(1, 3, "STM32!@skk");
	OLED_ShowNum(2, 1, 56889, 5);
	OLED_ShowSignedNum(2, 7, -10222, 5);
	OLED_ShowHexNum(3, 1, 0xFC65, 4);
	OLED_ShowBinNum(4, 1, 0xFC65, 16);
	
	// OLED_Clear();
	while (1)
	{
		
	}
}
