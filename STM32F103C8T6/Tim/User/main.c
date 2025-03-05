#include "Test_Timer.h"

int main(void)  
{
	// 测试内部定时器
	// testInternalTimer();
	
	// 测试外部时钟
	// testExternalTimer();	
	
	// 测试PWM控制LED呼吸灯(渐变)
	// testControlLED_PWM();
	
	// 测试PWM控制舵机
	testControlServo_PWM();
	
	
	return 0;
}

