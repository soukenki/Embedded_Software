#include "Test_ADC.h"

int main(void)  
{
	// 单通道
	// testOneADC();
	
	// 多通道 电位器+热敏+红外反射+光敏
	testMultipleADC();

	return 0;
}

