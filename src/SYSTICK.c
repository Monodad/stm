/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��usart.c
 * ����    ����શ�ʱ��ʵ��ms��ʱ��us��ʱ
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-04-08
 * Ӳ������: ��
 * ���Է�ʽ��J-Link-OB
 ********************************************************************************/
// ͷ�ļ�

#include "../include/SYSTICK.h"
static volatile uint32_t systick_delay = 0;

extern uint16_t nTime;

/**
 * @file   systick.c
 * @brief  ��ʼ��SYSTICK��1us�ж�1��
 * @param  ��
 * @retval ��
 */
uint32_t rcc_ahb_frequency = 16000000;
void systick_Init(void)
{
  /*SystemCoreClock/ 1000000��1us�ж�1�Σ�SystemCoreClock/ 1000��1ms�ж�һ��*/
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(rcc_ahb_frequency / 8 / 1000 - 1);

  systick_counter_enable();
  systick_interrupt_enable();
}

void delay_ms(uint32_t ms)
{
  systick_delay = ms;
  while (systick_delay != 0)
  {
    /* Wait. */
  }
}
