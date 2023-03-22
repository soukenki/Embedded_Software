#include <REGX52.H>

// 引脚配置：P0引脚没有上拉电阻，所以只显示第一排全黑
// sbit LCD_RS = P0^7;
// sbit LCD_RW = P0^6;
// sbit LCD_E = P0^5;

// 引脚配置：改P3引脚
sbit LCD_RS = P3^2;  // P32
sbit LCD_RW = P3^1;  // P31
sbit LCD_E = P3^0;   // P30

#define LCD_DataPort P2

// 延时 @12.000MHz
void Delay1ms(int num)		
{
	while (num--)
	{
		char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

// 写指令
void LCD_WriteCommand(unsigned char command) 
{
	LCD_E = 0;   // 使能清零
	LCD_RS = 0;   // 1为数据，0为指令
	LCD_RW = 0;   // 1为读，0为写
	
	LCD_DataPort = command;
	
	LCD_E = 1;
	Delay1ms(1);
	
	LCD_E = 0;
	Delay1ms(1);
}

// 写数据
void LCD_WriteData(unsigned char val)  
{
	LCD_E = 0;   // 使能清零
	LCD_RS = 1;   
	LCD_RW = 0;
	
	LCD_DataPort = val;
	
	LCD_E = 1;  // 先置高
	Delay1ms(1);
	
	LCD_E = 0;  // 再置低
	Delay1ms(1);
}

// 初始化
void LCD_Init()  
{
	LCD_WriteCommand(0x38);  // 八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);  // 显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);  // 数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);  // 光标复位，清屏
}

// 定位行列
void LCD_SetCursor(unsigned char line, unsigned char column) 
{
	if (line == 1)
	{
		LCD_WriteCommand(0x80 | (column - 0x01));
	}
	else
	{
		LCD_WriteCommand(0x80 | (column - 0x01) + 0x40);
	}
}

// 打印字符
void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char val)  
{
	LCD_SetCursor(line, column);
	
	LCD_WriteData(val);
}

// 打印字符串
void LCD_ShowArray(unsigned char line, unsigned char column, unsigned char* arr)  
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = 0; arr[i] != '\0'; ++i)
	{
		LCD_WriteData(arr[i]);
	}
}

// ret = x 的 y 次方
int LCD_Pow(int x, int y)  
{
	int i = 0;
	int ret = 1;
	
	for (i = 0; i < y; ++i)
	{
		ret *= x;
	}
	return ret;
}

// 打印无符号数
void LCD_ShowNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + num / LCD_Pow(10, i-1) % 10);
	}
}

// 打印有符号数
void LCD_ShowSignedNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	unsigned int newnum = 0;
	
	LCD_SetCursor(line, column);	
	
	if (num >= 0)
	{
		LCD_WriteData('+');
		newnum = num;
	}
	else
	{
		LCD_WriteData('-');
		newnum = -num;
	}
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + newnum / LCD_Pow(10, i-1) % 10);
	}
}

// 打印十六进制数
void LCD_ShowHexNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	unsigned char single_num = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		single_num = num / LCD_Pow(16, i-1) % 16;
		if (single_num < 10)
		{
			LCD_WriteData('0' + single_num);
		}
		else
		{
			LCD_WriteData('A' + single_num - 10);
		}		
	}
}

// 打印二进制数
void LCD_ShowBitNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + num / LCD_Pow(2, i-1) % 2);
	}
}

