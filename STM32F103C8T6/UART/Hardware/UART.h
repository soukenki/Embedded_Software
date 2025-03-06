#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


// UART pin口
#define UART_TX_PIN GPIO_Pin_9
#define UART_RX_PIN GPIO_Pin_10

#define UART_HEX_PACKET_MAX_SIZE    4
#define UART_HEX_PACKET_START   0xFF   // 包头
#define UART_HEX_PACKET_STOP    0xFE   // 包尾

#define UART_STR_PACKET_MAX_SIZE    128
#define UART_STR_PACKET_START   '@'    // 包头
#define UART_STR_PACKET_STOP_1  '\r'   // 包尾1
#define UART_STR_PACKET_STOP_2  '\n'   // 包尾2

// 数据包状态
enum Packet_Flag
{
    PACKET_NONE,
    PACKET_COMPLETE_HEX,    /*数据接收完整*/
    PACKET_COMPLETE_STRING,
    HEX_PACKET_START,   /*hex数据包*/
    HEX_PACKET_DATA,
    HEX_PACKET_STOP,
    STRING_PACKET_START,  /*文本数据包*/
    STRING_PACKET_DATA,
    STRING_PACKET_STOP,
};



// HEX数据包
extern uint8_t UART_TX_Hex_Packet[];
extern uint8_t UART_RX_Hex_Packet[];

// 文本数据包
extern char UART_RX_Str_Packet[];

// 数据包状态
extern uint8_t UART_RX_Complete_Flag;  



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


// 获取rx data
uint8_t UART_GetRxData(void);

// 获取数据包是否完整  只能调用一次，之后清0
uint8_t UART_GetCompleteFlag(void);

// 发送HEX数据包
void Uart_SendPacket(void);

#endif

