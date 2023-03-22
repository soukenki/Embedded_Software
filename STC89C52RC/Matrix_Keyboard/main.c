#include <REGX52.H>

#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char keynum = 0;  // 存放读取的键值


// 例1：1~16
void TestKeyDown()
{
	LCD_Init();
	LCD_ShowArray(1, 1, "MatrixKey:");
	
	while (1)
	{
		KeyDown(&keynum);
		LCD_ShowNum(2, 1, keynum, 2);
	}
}

//例2：1~16
void TestMatrixKey()
{
	LCD_Init();
	LCD_ShowArray(1, 1, "MatrixKey:");	

	while (1)
	{
		keynum =  MatrixKey();
		if (keynum)
		{
			LCD_ShowNum(2, 1, keynum, 2);
		}
	}
}

void TestPassword()
{
	LCD_Init();
	LCD_ShowArray(1, 1, "Password:");
	
	Password(&keynum);
}

void main()
{
	// TestKeyDown();
	// TestMatrixKey();
	TestPassword();
}