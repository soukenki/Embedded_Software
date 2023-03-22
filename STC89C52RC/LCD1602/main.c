#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD_Init();
	
	// test
	LCD_ShowChar(1, 1, 'A');
	LCD_ShowChar(1, 2, '\\');
	LCD_ShowArray(2, 1, "skk");
	LCD_ShowNum(1, 4, 6666, 4);
	LCD_ShowSignedNum(1, 9, -1234, 4);
	LCD_ShowHexNum(2, 5, 0xA5, 2);
	LCD_ShowBitNum(2, 8, 0xA2, 8);
	LCD_ShowChar(2, 16, 0xDF);
	
	LCD_ShowArray(1, 16, "Welcome to kanazawa!");
	while (1)
	{
		LCD_WriteCommand(0x18);  // 发生指令，屏幕滚动
		Delay1ms(1000);
		
		// LCD_WriteCommand(0x06);  // 不滚动
		// Delay1ms(1000);
	}
}