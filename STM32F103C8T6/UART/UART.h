#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


// 初始化UART
void UART_Init(void);

// 写一个字节
void UART_SendByte(uint8_t byte);

// 写一个数组
void UART_SendArray(uint8_t *arr, uint16_t len);

// 写一个字符串
void UART_SendString(char *str);

// 写数字
void UART_SendNumber(uint32_t num, uint8_t len);

// 可变参数的printf
void UART_Printf(char *format, ...);

// 获取rx flag
uint8_t UART_GetRxFlag(void);

// 获取rx data
uint8_t UART_GetRxData(void);

#endif

