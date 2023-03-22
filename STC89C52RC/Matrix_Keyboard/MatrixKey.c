#include "MatrixKey.h"

#define GPIO_KEY P1



// 例1：1~16
void KeyDown(unsigned char* keynum)
{
	char a = 0;
	GPIO_KEY = 0x0F;
	if (GPIO_KEY != 0x0F)  // 读取按键是否按下
	{
		Delay(10); // 延时10ms进行消抖
		if (GPIO_KEY != 0x0F)  // 再次检测按下
		{
			// 测试列
			GPIO_KEY = 0x0F;
			switch (GPIO_KEY)
			{
				case(0x07): 
					*keynum = 16; break;
				case(0x0B): 
					*keynum = 12; break;
				case(0x0D): 
					*keynum = 8; break;
				case(0x0E): 
					*keynum = 4; break;
			}
			
			// 测试行
			GPIO_KEY = 0xF0;
			switch (GPIO_KEY)
			{
				case(0x70): 
					*keynum = *keynum; break;
				case(0xB0): 
					*keynum = *keynum-1; break;
				case(0xD0): 
					*keynum = *keynum-2; break;
				case(0xE0): 
					*keynum = *keynum-3; break;
			}
			
			while ((a < 50) && (GPIO_KEY != 0xF0))  // 检测按键松手
			{
				Delay(10);
				a++;
			}
		}
	}
}


// 例2：1~16

unsigned char MatrixKey()

{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=16;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=15;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=14;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=12;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=11;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=9;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=8;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=6;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=5;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=3;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=2;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=1;}
	
	return KeyNumber;
}

void Password(unsigned char* keynum)
{
	unsigned int password = 0;  // 存放密码
	unsigned int count = 0;  // 计数
	
	while (1)
	{
		*keynum =  MatrixKey();
		if (*keynum)
		{
			if (*keynum <= 10)  // 如果S1~S10按键按下，输入密码
			{
				if (count < 4)  // 4位密码
				{
					password *= 10;
					password += (*keynum % 10);  // 获取一位密码
					count++;
				}
				LCD_ShowNum(2, 1, password, 4); // 更新显示
			}
			
			if (*keynum == 11)  // 如果S11按下，确认
			{
				if (password == 718) // 正确密码
				{
					LCD_ShowArray(1, 14, "OK ");
					// 这里可以跳转
					// ....
					password = 0;   // 清零重新输入
					count = 0;
					LCD_ShowNum(2, 1, password, 4); // 更新显示
					Delay(1500);
					LCD_ShowArray(1, 14, "   ");
				}
				else
				{
					LCD_ShowArray(1, 14, "ERR");
					password = 0;   // 清零重新输入
					count = 0;
					LCD_ShowNum(2, 1, password, 4); // 更新显示 
					Delay(1500);
					LCD_ShowArray(1, 14, "   ");
				}
			}
			if (*keynum == 12) // 如果S12按下，取消
			{
				password = 0;   // 清零
				count = 0;
				LCD_ShowNum(2, 1, password, 4); // 更新显示 
			}
		}
	}
}