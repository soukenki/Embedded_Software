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
	// PWM_Init_AFIO();  // PA0重映射到PA15
	
	OLED_ShowString(1, 1, "testControlLED_PWM");
	int i = 0;
	while (1)
	{
		for (i = 0; i < 100; i++)
		{
			PWM_SetCompare1(i); // 不断增加CCR的值，达到LED渐亮
			// 这里不是直接改变占空比，因为占空比是CCR和ARR+1共同决定的
			// 因为ARR+1现在设置固定值100，所以这里CCR的值才直接等于占空比
			Delay_ms(10);
		}
		
		for (i = 0; i < 100; i++)
		{
			PWM_SetCompare1(100 - i);  // 减低CRR值，LED渐暗
			Delay_ms(10);
		}
	}
}

// 测试PWM控制舵机  
void testControlServo_PWM()
{
	OLED_Init();
	Servo_Init(); // 舵机PWM初始化

	while (1)
	{
		Servo_SetAngle(0); // 调整角度
		Delay_ms(1000);
		Servo_SetAngle(45);
		Delay_ms(1000);
		Servo_SetAngle(90);
		Delay_ms(1000);
		Servo_SetAngle(135);
		Delay_ms(1000);
		Servo_SetAngle(180);
		Delay_ms(1000);
	}
}

