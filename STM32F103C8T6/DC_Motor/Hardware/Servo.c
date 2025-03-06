#include "Servo.h"

// 初始化舵机
void Servo_Init()
{
	PWM_Init_Servo();
}

// 设置角度 0，90，180
void Servo_SetAngle(float Angle)
{
	// 初始化用的通道2，所以这里修改通道2
	PWM_SetCompare2(Angle / 180 * 2000 + 500);
}
