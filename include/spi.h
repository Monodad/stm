#ifndef __SPI_H
#define __SPI_H
// #include "sys.h"
#include <libopencm3/stm32/spi.h>
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
// ALIENTEKս��STM32������
// SPI���� ����
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// �޸�����:2012/9/9
// �汾��V1.0
// ��Ȩ���У�����ؾ���
// Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

void SPI1_Init(void);                       // ��ʼ��SPI��
void SPI1_SetSpeed(uint8_t SpeedSet);       // ����SPI�ٶ�
uint8_t SPI1_ReadWriteByte(uint8_t TxData); // SPI���߶�дһ���ֽ�

#endif
