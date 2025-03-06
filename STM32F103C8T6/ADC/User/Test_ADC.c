#include "Test_ADC.h"



// 单通道 电位器
void testOneADC(void)
{
	OLED_Init();
	AD_Init_One();
	
	uint16_t ad_value = 0; // AD数据
	float voltage = 0; // 电压
	
	OLED_ShowString(1, 1, "ad_value:");
	OLED_ShowString(2, 1, "voltage:0.00V");
	
	while (1)
	{
		ad_value = AD_GetValue_One();
		voltage = (float)ad_value / 4095 * 3.3; // AD值计算电压
		
		OLED_ShowNum(1, 10, ad_value, 4);
		OLED_ShowNum(2, 9, voltage, 1);   // 电压个位
		OLED_ShowNum(2, 11, (uint16_t)(voltage * 100) % 100, 2); // 电压小数位
		
		Delay_ms(100);
	}
}


// 多通道 电位器+热敏+红外反射+光敏
void testMultipleADC(void)
{
	OLED_Init();
	AD_Init_Multiple();
	
	uint16_t ad_0 = 0; // 电位
	uint16_t ad_1 = 0; // 热敏
	uint16_t ad_2 = 0; // 红外反射
	uint16_t ad_3 = 0; // 光敏
	
	OLED_ShowString(1, 1, "ad_0:");
	OLED_ShowString(2, 1, "ad_1:");
	OLED_ShowString(3, 1, "ad_2:");
	OLED_ShowString(4, 1, "ad_3:");
	
	while (1)
	{
		ad_0 = AD_GetValue_Multiple(ADC_Channel_0);
		ad_1 = AD_GetValue_Multiple(ADC_Channel_1);
		ad_2 = AD_GetValue_Multiple(ADC_Channel_2);
		ad_3 = AD_GetValue_Multiple(ADC_Channel_3);
		
		OLED_ShowNum(1, 6, ad_0, 4);
		OLED_ShowNum(1, 11, ((float)ad_0 / 4095 * 3.3), 1);   // 电压个位
		OLED_ShowString(1, 12, ".");
		OLED_ShowNum(1, 13, (uint16_t)(((float)ad_0 / 4095 * 3.3) * 100) % 100, 2); // 电压小数位
		
		OLED_ShowNum(2, 6, ad_1, 4);
		OLED_ShowNum(2, 11, ((float)ad_1 / 4095 * 3.3), 1);   // 电压个位
		OLED_ShowString(2, 12, ".");
		OLED_ShowNum(2, 13, (uint16_t)(((float)ad_1 / 4095 * 3.3) * 100) % 100, 2); // 电压小数位

		OLED_ShowNum(3, 6, ad_2, 4);
		OLED_ShowNum(3, 11, ((float)ad_2 / 4095 * 3.3), 1);   // 电压个位
		OLED_ShowString(3, 12, ".");
		OLED_ShowNum(3, 13, (uint16_t)(((float)ad_2 / 4095 * 3.3) * 100) % 100, 2); // 电压小数位

		OLED_ShowNum(4, 6, ad_3, 4);
		OLED_ShowNum(4, 11, ((float)ad_3 / 4095 * 3.3), 1);   // 电压个位
		OLED_ShowString(4, 12, ".");
		OLED_ShowNum(4, 13, (uint16_t)(((float)ad_3 / 4095 * 3.3) * 100) % 100, 2); // 电压小数位
				
		Delay_ms(100);
	}
}
