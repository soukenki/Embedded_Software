#ifndef __Timer_H__
#define __Timer_H__

#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"

// 初始化定时器
void Timer0_Init();

// 独立按键函数
unsigned char Key();

// 1ms等待@11.0592MHz (与LCD中的延时函数冲突，这里注释掉)
//void Delay1ms(unsigned int xms);	

// 测试独立按钮
void testTimer1();

// 测试独立按键控制流水灯（定时器实现）
void testTimer2();

// 测试LCD时钟（定时器实现）
void testTimer3();

#endif