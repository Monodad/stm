#ifndef __ADC_H
#define __ADC_H
#include "SYSTICK.h"
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

void Adc_Init(void);
uint16_t Get_Adc0(uint8_t ch);
uint16_t Get_Adc1(uint8_t ch);
uint16_t Get_Adc4(uint8_t ch);

uint16_t Get_Adc_Average0(uint8_t ch, uint8_t times);
uint16_t Get_Adc_Average1(uint8_t ch, uint8_t times);
uint16_t Get_Adc_Average4(uint8_t ch, uint8_t times);

void ADC0_Temp_jiance(void);
void ADC1_Temp_jiance(void);
void ADC_Voltage_jiance(void);
#endif
