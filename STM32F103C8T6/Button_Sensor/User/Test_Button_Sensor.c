#include "Test_Button_Sensor.h"

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
void testLightSensor()
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

// 测试红外传感器
void testInfraredSensor()
{
	OLED_Init();
	InfraredSensor_Init();
	
	OLED_ShowString(1, 1, "Count:");
	while (1)
	{
		OLED_ShowNum(1, 8, InfraredSensor_Get(), 5);
		
	}
	
	
}












