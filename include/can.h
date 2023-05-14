#ifndef __CAN_H
#define __CAN_H
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
// ALIENTEKս��STM32������
// CAN���� ����
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// ��������:2014/5/7
// �汾��V1.1
// ��Ȩ���У�����ؾ���
// Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
// All rights reserved
//********************************************************************************
// V1.1�޸�˵�� 20150528
// ������CAN��ʼ�����������ע�ͣ������˲����ʼ��㹫ʽ
//////////////////////////////////////////////////////////////////////////////////

// CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE 0 // 0,��ʹ��;1,ʹ��.

uint8_t CAN_Mode_Init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode); // CAN��ʼ��

uint32_t Can_Send_Msg(uint8_t *msg, uint8_t len, uint32_t appid);

uint8_t Can_Receive_Msg(uint8_t *buf); // ��������
#endif
