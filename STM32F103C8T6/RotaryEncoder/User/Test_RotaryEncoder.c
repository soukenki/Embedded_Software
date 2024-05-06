#include "Test_RotaryEncoder.h"


// 旋转编码器
void testRotaryEncoder(void)
{
	int16_t num = 0;
	
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1, 1, "num:");
	while (1)
	{
		num += Encoder_Get();
		OLED_ShowSignedNum(1, 5, num, 5);
	}	
}









