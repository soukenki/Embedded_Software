#ifndef __LCD1602_H__
#define __LCD1602_H__

// 屏幕 16*2
// DDRAM 40*2

// 延时
void Delay1ms(int num);

// 写指令
void LCD_WriteCommand(unsigned char command);
// 写数据
void LCD_WriteData(unsigned char val);

// 初始化
void LCD_Init();

// 打印字符
void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char val);
// 打印字符串
void LCD_ShowArray(unsigned char line, unsigned char column, unsigned char* arr);
// 打印有符号数
void LCD_ShowNum(unsigned char line, unsigned char column, int num, unsigned char len);
// 打印无符号数
void LCD_ShowSignedNum(unsigned char line, unsigned char column, int num, unsigned char len);
// 打印十六进制数
void LCD_ShowHexNum(unsigned char line, unsigned char column, int num, unsigned char len);
// 打印二进制数
void LCD_ShowBitNum(unsigned char line, unsigned char column, int num, unsigned char len);

#endif