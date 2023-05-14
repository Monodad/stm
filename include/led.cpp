/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��led.c
 * ����    ��LED����������
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-04-08
 * Ӳ������: D1->PC13;D2->PB0;D3->PB1
 * ���Է�ʽ��J-Link-OB
 **********************************************************************************/

// ͷ�ļ�
#include "led.h"
#include "SYSTICK.h"
/**
 * @file   LED_GPIO_Config
 * @brief  LED����������
 * @param  ��
 * @retval ��
 */
void LED_GPIO_Config(void)
{
  // ����һ��GPIO_InitTypeDef ���͵Ľṹ��
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIO������ʱ��
  /*D1*/

  /*D5*/
  GPIO_InitStructure.GPIO_Pin = LED5_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @file   LEDXToggle
 * @brief  LED����ת
 * @param  ledx:1--PC13;2--PB0;3--PB1
 * @retval ��
 */
void LEDXToggle(uint8_t ledx)
{
  if (ledx == 5)
  {
    LED5_GPIO_PORT->ODR ^= LED5_GPIO_PIN;
  }
}
