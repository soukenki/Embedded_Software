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
	// testControlServo_PWM();
	
	// 测试按键控制舵机
	// testControlServo_Key();
	
	// 测试PWM控制直流电机
	// testControlDC_Motor_PWM();
	
	// 测试按键控制直流电机
	// testControlDC_Motor_Key();
	
	// 测试定时器输入捕获测频率
	// testPWMFreq();
	
	// 测试PWMI输入捕获测频率+占空比
	testPWMIFreqDuty();
	
	return 0;
}

