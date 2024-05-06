#ifndef __TEST_TIMER_H__
#define __TEST_TIMER_H__

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

// 测试内部定时器
extern void testInternalTimer(void);

// 测试外部时钟
extern void testExternalTimer(void);

#endif
