#include "Button_Sensor.h"

// 测试按钮控制LED
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