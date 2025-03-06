#include "Test_LED_Buzzer.h"

// 按钮控制LED
void testButton(void)
{
	uint8_t ButtonNum = 0;
	
	LED_Init();
	Button_Init();
	
	while (1)
	{
		ButtonNum = Button_GetNum();
		if (1 == ButtonNum)
		{
			LEDTurn(0);
		}
		if (2 == ButtonNum)
		{
			LEDTurn(1);
		}
	}
}

// 测试蜂鸣器
void testBuzzer(void)
{
	Buzzer_Init();
	
	while (1)
	{
		Buzzer_ON();
		Delay_ms(500);
		Buzzer_OFF();
		Delay_ms(500);
		
		BuzzerTurn();
		Delay_ms(500);
		BuzzerTurn();
		Delay_ms(500);
	}
}

// 测试光传感
void testLightSensor(void)
{
	Buzzer_Init();
	LightSensor_Init();
	
	while (1)
	{
		if (1 == LightSensor_Get())
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	}
}


// 测试OLED
void testOLED(void)
{
	OLED_Init();
	
	OLED_ShowChar(1, 1, 'K');              // 字符串
	OLED_ShowString(1, 3, "STM32!@skk");   // 字符串
	OLED_ShowNum(2, 1, 56889, 5);          // 行，列，无符号数字，长度 
	OLED_ShowSignedNum(2, 7, -10222, 5);   // 行，列，有符号数字，长度
	OLED_ShowHexNum(3, 1, 0xFC65, 4);      // 行，列，16进制数，长度	
	OLED_ShowBinNum(4, 1, 0xFC65, 16);     // 行，列，二进制数，长度
	
	// OLED_Clear();  // 全屏清屏
	// 如果只清除部分位置，用OLED_ShowString在该位置输出空格即可
	while (1)
	{
		
	}
}
