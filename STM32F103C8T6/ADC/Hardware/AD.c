#include "AD.h"

FunctionalState EN_ADC_ContinuousConvMode = ENABLE;  // 当前为-连续/单次模式

// 单通道
void AD_Init_One(void)
{
	// 开启RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // ADC时钟，ADC都是APB2上的设备
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // GPIO时钟
	
	// ADCCLK分频器
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 2/4/6/8分频
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入模式（使GPIO口无效，防止GPIO的输入输出对模拟电压造成干扰）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置多路开关 通道->规则组
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 规则组，通道0，序列1，采样时间555（越小越快，越大越稳定）
	
	// 结构体初始化 配置ADC
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_FastInterl;  // 独立 - 工作模式：独立模式/双ADC模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐 - 数据对齐：左对齐/右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发（不触发）- 外部触发转换选择（触发源）
	// ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次 - 连续转换模式：连续/单次
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 非扫描 - 扫描模式：扫描/非扫描
	ADC_InitStructure.ADC_NbrOfChannel = 1; // 通道数目：1~16
	
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 模拟看门狗
	// todo
	
	// 开关控制
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC校准（上电使能后需要校准）
	ADC_ResetCalibration(ADC1); // 复位校准
	while (SET == ADC_GetResetCalibrationStatus(ADC1)); // 等待复位校准状态完成
	ADC_StartCalibration(ADC1); // 启动校准
	while(SET == ADC_GetCalibrationStatus(ADC1)); // 等待开始校准状态完成
	
	if (ENABLE == ADC_InitStructure.ADC_ContinuousConvMode)
	{
		EN_ADC_ContinuousConvMode = ENABLE; // 连续
		ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 连续转换时，只需一次触发
	}
	else
	{
		EN_ADC_ContinuousConvMode = DISABLE; // 单次
	}
}

// 启动转换 获取结果 （单通道）
uint16_t AD_GetValue_One(void)
{
	if (DISABLE == EN_ADC_ContinuousConvMode) // 单次
	{
		// 软件触发
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
		// 等待转换完成（EOC置1）
		while (RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); // 等待转换完成
	
		// 取结果
		return ADC_GetConversionValue(ADC1);
	}
	else
	{
		return ADC_GetConversionValue(ADC1); // 连续
	}
}


// 多通道
void AD_Init_Multiple(void)
{
	// 开启RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // ADC时钟，ADC都是APB2上的设备
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // GPIO时钟
	
	// ADCCLK分频器
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 2/4/6/8分频
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入模式（使GPIO口无效，防止GPIO的输入输出对模拟电压造成干扰）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	// 结构体初始化 配置ADC
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_FastInterl;  // 独立 - 工作模式：独立模式/双ADC模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐 - 数据对齐：左对齐/右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发（不触发）- 外部触发转换选择（触发源）
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次 - 连续转换模式：连续/单次
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 非扫描 - 扫描模式：扫描/非扫描
	ADC_InitStructure.ADC_NbrOfChannel = 1; // 通道数目：1~16
	
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 模拟看门狗
	// todo
	
	// 开关控制
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC校准（上电使能后需要校准）
	ADC_ResetCalibration(ADC1); // 复位校准
	while (SET == ADC_GetResetCalibrationStatus(ADC1)); // 等待复位校准状态完成
	ADC_StartCalibration(ADC1); // 启动校准
	while(SET == ADC_GetCalibrationStatus(ADC1)); // 等待开始校准状态完成
	
	if (ENABLE == ADC_InitStructure.ADC_ContinuousConvMode)
	{
		EN_ADC_ContinuousConvMode = ENABLE; // 连续
		ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 连续转换时，只需一次触发
	}
	else
	{
		EN_ADC_ContinuousConvMode = DISABLE; // 单次
	}
}

// 启动转换 获取结果 （多通道）
uint16_t AD_GetValue_Multiple(uint8_t ADC_Channel)
{
	// 配置 通道
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 传参通道，每次变更通道来实现多通道

	if (DISABLE == EN_ADC_ContinuousConvMode) // 单次
	{
		// 软件触发
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
		// 等待转换完成（EOC置1）
		while (RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); // 等待转换完成
	
		// 取结果
		return ADC_GetConversionValue(ADC1);
	}
	else
	{
		return ADC_GetConversionValue(ADC1); // 连续
	}
}

