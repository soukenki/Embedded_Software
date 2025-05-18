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

// 测试按键控制舵机
void testControlServo_Key()
{
	OLED_Init();
	Button_Init();
	Servo_Init(); // 舵机初始化
	
	OLED_ShowString(1, 1, "Angle:");
	
	uint8_t key_num = 0;
	float angle = 0.0;
	
	while (1)
	{
		key_num = Button_GetNum();
		if (1 == key_num)
		{
			angle += 30; // 每次按下按钮增加30度
			if (angle > 180)
			{
				angle = 180;
			}
		}
		else if (2 == key_num)
		{
			angle -= 30; // 每次按下按钮减30度
			if (angle < 0)
			{
				angle = 0;
			}
		}
		Servo_SetAngle(angle); // 调整角度
		OLED_ShowNum(1, 7, angle, 3);
	}
}

// 测试PWM控制直流电机
void testControlDC_Motor_PWM()
{
	DC_Motor_Init(); // 初始化直流电机
	
	while (1)
	{
		DC_Motor_SetSpeed(30); // 最大速度100 , 正负数 控制 正反转
		Delay_ms(1000);
		DC_Motor_SetSpeed(60);
		Delay_ms(1000);
		DC_Motor_SetSpeed(100);
		Delay_ms(1000);
		DC_Motor_SetSpeed(60);
		Delay_ms(1000);
	}
}

// 测试按键控制直流电机
void testControlDC_Motor_Key()
{
	OLED_Init();
	Button_Init();
	DC_Motor_Init(); // 舵机初始化
	
	OLED_ShowString(1, 1, "Speed:");
	
	uint8_t key_num = 0;
	int8_t speed = 0;
	
	while (1)
	{
		key_num = Button_GetNum();
		if (1 == key_num)
		{
			speed += 10; // 每次按下按钮增加20速度
			if (speed > 100)
			{
				speed = 100;
			}
		}
		else if (2 == key_num)
		{
			speed -= 10;
			if (speed < -100)
			{
				speed = -100;
			}
		}
		DC_Motor_SetSpeed(speed); // 调整速度
		OLED_ShowSignedNum(1, 7, speed, 3);
	}
}
