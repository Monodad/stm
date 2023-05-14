#include "adc.h"
#include "SYSTICK.h"
#include "math.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
// ALIENTEKս��STM32������
// ADC ����
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// �޸�����:2012/9/7
// �汾��V1.0
// ��Ȩ���У�����ؾ���
// Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

// ��ʼ��ADC
// �������ǽ��Թ���ͨ��Ϊ��
// ����Ĭ�Ͻ�����ͨ��0~3
void Adc_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE); // ʹ��ADC1ͨ��ʱ��

	RCC_ADCCLKConfig(RCC_PCLK2_Div2); // ����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PA0 ��Ϊģ��ͨ����������

	ADC_DeInit(ADC1); // ��λADC1

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					// ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						// ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					// ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // ת���������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				// ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;								// ˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);									// ����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	ADC_Cmd(ADC1, ENABLE); // ʹ��ָ����ADC1

	ADC_ResetCalibration(ADC1); // ʹ�ܸ�λУ׼

	while (ADC_GetResetCalibrationStatus(ADC1))
		; // �ȴ���λУ׼����

	ADC_StartCalibration(ADC1); // ����ADУ׼

	while (ADC_GetCalibrationStatus(ADC1))
		; // �ȴ�У׼����

	//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������
}
// ���ADCֵ
// ch:ͨ��ֵ 0~3
u16 Get_Adc0(u8 ch)
{
	// ����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5); // ADC1,ADCͨ��,����ʱ��Ϊ239.5����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);										 // ʹ��ָ����ADC1������ת����������

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		; // �ȴ�ת������

	return ADC_GetConversionValue(ADC1); // �������һ��ADC1�������ת�����
}

u16 Get_Adc1(u8 ch)
{
	// ����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5); // ADC1,ADCͨ��,����ʱ��Ϊ239.5����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);										 // ʹ��ָ����ADC1������ת����������

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		; // �ȴ�ת������

	return ADC_GetConversionValue(ADC1); // �������һ��ADC1�������ת�����
}

u16 Get_Adc4(u8 ch)
{
	// ����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5); // ADC1,ADCͨ��,����ʱ��Ϊ239.5����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);										 // ʹ��ָ����ADC1������ת����������

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		; // �ȴ�ת������

	return ADC_GetConversionValue(ADC1); // �������һ��ADC1�������ת�����
}

u16 Get_Adc_Average0(u8 ch, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for (t = 0; t < times; t++)
	{
		temp_val += Get_Adc0(ch);
		delay_ms(5);
	}
	return temp_val / times;
}

u16 Get_Adc_Average1(u8 ch, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for (t = 0; t < times; t++)
	{
		temp_val += Get_Adc1(ch);
		delay_ms(5);
	}
	return temp_val / times;
}

u16 Get_Adc_Average4(u8 ch, u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for (t = 0; t < times; t++)
	{
		temp_val += Get_Adc4(ch);
		delay_ms(5);
	}
	return temp_val / times;
}

int Batt[50] = {0};
void ADC0_Temp_jiance()
{

	float ADC0_Temp = 0;
	float Adc_value1, BAT_value;

	float Rt = 0;
	float Rp = 10000;
	float T2 = 273.15 + 25;
	float Bx = 3950;
	float Ka = 273.15;
	unsigned char readTempbuf[2];
	int TempRes;
	unsigned char Tempbuf[1];

	Adc_value1 = Get_Adc_Average0(1, 10);
	BAT_value = (float)(3.3 * Adc_value1 / 4096);

	TempRes = 10000 * BAT_value / (3.3 - BAT_value);
	ADC0_Temp = 1 / (1 / T2 + (log(TempRes / Rp)) / Bx) - Ka + 0.5;
	//	 shang[5]=ADC0_Temp;
	Batt[0] = ADC0_Temp;
}

void ADC1_Temp_jiance()
{
	float ADC1_Temp = 0;
	float Adc_value1, BAT_value;

	float Rt = 0;
	float Rp = 10000;
	float T2 = 273.15 + 25;
	float Bx = 3950;
	float Ka = 273.15;
	unsigned char readTempbuf[2];
	int TempRes;
	unsigned char Tempbuf[1];

	Adc_value1 = Get_Adc_Average1(1, 10);
	BAT_value = (float)(3.3 * Adc_value1 / 4096);

	TempRes = 10000 * BAT_value / (3.3 - BAT_value);
	ADC1_Temp = 1 / (1 / T2 + (log(TempRes / Rp)) / Bx) - Ka + 0.5;
	//		shang[6]=ADC1_Temp;
	Batt[1] = ADC1_Temp;
}

float BAT_tol_value;
float Adc_value2;
void ADC_Voltage_jiance()
{
	Adc_value2 = Get_Adc_Average4(1, 10);
	BAT_tol_value = (float)(3.3 * Adc_value2 / 4096);
	Batt[2] = BAT_tol_value * 1000;
}
