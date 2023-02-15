#include <REGX52.H>
#include <INTRINS.H>

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay1ms(unsigned int xms)		//@12.000MHz
{
	do
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}while (--xms);
}

void Flash() // 闪烁
{
	while (1)
	{	
		P1 = 0xFE;
		Delay500ms();
		P1 = 0xFF;
		Delay500ms();
	}
}

void Gradient1() // 流水灯1  逐渐满
{
	do
	{
		unsigned char i;
		P1 = 0xFF;
		i = 0x01;
		while (i != 0x00)
		{
			P1 = P1 ^ i;  // 0xFF->0x00->0xFF
			i = i << 1;
			Delay500ms();
		}
	}while (1);
}

void Gradient2()  // 流水灯2  逐位跳动
{
	do
	{
		P1 = 0xFE;
		while (P1 != 0xFF)
		{
			Delay1ms(100);
			P1 = ~((~P1) << 1);  
		}
	}while (1);
}

void Button1()  // 按钮 按住点亮
{
	while (1)
	{
		if (P3_5 == 0)  // 按下按钮S1输出负电
		{
			P1_0 = 0;
		}
		else
		{
			P1_0 = 1;   // 否则正电
		}
	}
}

void Button2()  // 按一下 点亮 / 灭
{
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(20);  // 消抖 延时20ms
			while (P3_5 == 0) ;  // 按下期间等待
			Delay1ms(20);
			
			P1_0 = ~P1_0;   // 按下->取反->亮/灭
		}
	}
}

void Button3()  // 二进制按钮点灯
{
	unsigned char LEDNum = 0;
	
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(250);  // 消抖 250ms是为了区分长按和短按
			while (P3_5 == 0)  
			{
				Delay1ms(20);
				if (P3_5 == 0)   // 长按 一直进位
				{
					++LEDNum;
					P1 =  ~LEDNum;
				}
				Delay1ms(20);				
			}
			Delay1ms(20);
			
			// 短按 每次进一位
			++LEDNum;
			P1 =  ~LEDNum;
		}
	}
}

void Button4()  // 按钮控制LED左右移位
{
	unsigned char LEDNum = 0;
	P1 = 0xFE;   // 
	
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(250);  // 消抖 250ms是为了区分长按和短按
			
			while (P3_5 == 0)  
			{
				Delay1ms(100);  // 降速
				
				if (P3_5 == 0)
				{
					// 长按 一直移位				
					++LEDNum;   
					if (LEDNum >= 8)
					{
						LEDNum = 0;
					}
					P1 =  ~(0x01 << LEDNum);	
				}
				
				Delay1ms(20);				
			}
			
			Delay1ms(20);
			
			// 短按 每次移一位
			++LEDNum;
			if (LEDNum >= 8)
			{
				LEDNum = 0;
			}
			P1 =  ~(0x01 << LEDNum);	
		}
		
		if (P3_4 == 0)
		{
			Delay1ms(250);  // 消抖 250ms是为了区分长按和短按
			
			while (P3_4 == 0)  
			{
				Delay1ms(100);  // 降速
				
				if (P3_4 == 0)
				{
					// 长按 一直移位
					if (LEDNum == 0)
					{
						LEDNum = 7;
					}
					else
					{
						--LEDNum;
					}
					P1 =  ~(0x01 << LEDNum);
				}
				
				Delay1ms(20);				
			}
			
			Delay1ms(20);
			
			// 短按 每次移一位
			if (LEDNum == 0)
			{
				LEDNum = 7;
			}
			else
			{
				--LEDNum;
			}
			P1 =  ~(0x01 << LEDNum);
		}
	}
}


void main()
{
	// P1 = 0xFE; // 1111 1110 点亮单个LED
	// P1 = 0xAA; // 1010 1010 多个


	// Flash();  // 闪烁
	// Gradient1();  // 逐渐满
	// Gradient2();  // 逐位跳动
	// Button1();  // 按住S1点亮
	// Button2();  // 按下->取反->亮/灭
	// Button3();   // 二进制点灯
	Button4();   // LED左右移位
	
}