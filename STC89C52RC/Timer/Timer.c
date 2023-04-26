#include "Timer.h"
 
unsigned char LEDMode = 0;
unsigned char Sec, Min, Hour;

// 1ms等待@11.0592MHz  (与LCD中的延时函数冲突，这里注释掉)
//void Delay1ms(unsigned int xms)
//{
//	do
//	{
//		unsigned char i, j;

//		i = 2;
//		j = 199;
//		do
//		{
//			while (--j);
//		} while (--i);
//	}while (--xms);
//}

// 独立按键函数  范围0~4  无按键按下时，返回0
unsigned char Key()
{
	unsigned char KeyNum = 0;
	if (P3_5 == 0)
	{
		Delay1ms(20);
		while (P3_5 == 0);
		Delay1ms(20);
		KeyNum = 1;
	}
	
	if (P3_4 == 0)
	{
		Delay1ms(20);
		while (P3_4 == 0);
		Delay1ms(20);
		KeyNum = 2;
	}
	
	if (P3_3 == 0)
	{
		Delay1ms(20);
		while (P3_3 == 0);
		Delay1ms(20);
		KeyNum = 3;
	}
	
	if (P3_2 == 0)
	{
		Delay1ms(20);
		while (P3_2 == 0);
		Delay1ms(20);
		KeyNum = 4;
	}
	return KeyNum;
}

// 初始化定时器
void Timer0_Init()     // 1毫秒@11.0592MHz
{
	//TMOD = 0x01;  // 0000 0001
	TMOD &= 0xF0;  // 把TMTD的低4位清零，高4位保持不变
	TMOD |= 0x01;  // 把TMTD的低4位置为1，高4位保持不变
	
	TF0 = 0;    // 清除TF0标志
	TR0 = 1;    // 定时器0开始计时
	
	// TH0 = 64535/256+1;   // 0x18
	// TL0 = 64535%256+1;   // 0xFC
	TL0 = 0x18;		// 设置定时初值
	TH0 = 0xFC;		// 设置定时初值
	
	// 设置中断
	ET0 = 1;
	EA = 1;
	PT0 = 0;

}

// 中断 (控制流水灯)
void Timer0_Routine1() interrupt 2
{
	static unsigned int T0Count = 0;
	
	TL0 = 0x18;		// 设置定时初值
	TH0 = 0xFC;		// 设置定时初值
	
	T0Count++;
	if (T0Count >= 500)  // 0.5秒
	{	
		T0Count = 0;
		if (LEDMode == 0)
			P1 = _crol_(P1, 1);  // 循环左移
		if (LEDMode == 1)
			P1 = _cror_(P1, 1);  // 循环右移

	}
}


// 测试独立按钮
void testTimer1()
{
	unsigned char KeyNum;
	
	while (1)
	{
		KeyNum = Key();
		if (KeyNum)
		{
			if (KeyNum == 1){P1_0 = ~P1_0;}
			if (KeyNum == 2){P1_1 = ~P1_1;}
			if (KeyNum == 3){P1_2 = ~P1_2;}
			if (KeyNum == 4){P1_3 = ~P1_3;}			
		}
	}
}



// 测试独立按键控制流水灯（定时器实现）
void testTimer2()
{
	unsigned char KeyNum = 0;

	P1 = 0xFE;
	Timer0_Init();
	while (1)
	{
		KeyNum = Key();
		if (KeyNum)
		{
			if (KeyNum == 1)
			{
				LEDMode++;
				if (LEDMode >= 2)
					LEDMode = 0;
			}
		}
	}
}


// 中断 (控制时钟)
void Timer0_Routine2() interrupt 1
{
	static unsigned int T0Count = 0;
	
	TL0 = 0x18;		// 设置定时初值
	TH0 = 0xFC;		// 设置定时初值
	
	T0Count++;
	if (T0Count >= 1000)  // 1秒
	{	
		T0Count = 0;
		Sec++;
		if (Sec >= 60)
		{
			Sec = 0;
			Min++;
			if (Min >= 60)
			{
				Min = 0;
				Hour++;
				if (Hour >= 24)
				{	
					Hour = 0;
				}
			}
		}
	}
}

// 测试LCD时钟（定时器实现）
void testTimer3()
{
	LCD_Init();     // LCD初始化
	Timer0_Init();  // 定时器初始化
	Sec = 55;
	Min = 59;
	Hour = 23;
	LCD_ShowArray(1, 1, "Clock:");
	LCD_ShowArray(2, 1, "  :  :");
	while (1)
	{
		LCD_ShowNum(2, 1, Hour, 2);
		LCD_ShowNum(2, 4, Min, 2);
		LCD_ShowNum(2, 7, Sec, 2);
	}
}