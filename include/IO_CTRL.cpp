/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��IO_CTRL.c
 * ����    ��IO����������
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-04-08
 * Ӳ������: D1->PC13;D2->PB0;D3->PB1
 * ���Է�ʽ��J-Link-OB
 **********************************************************************************/

// ͷ�ļ�
#include "IO_CTRL.h"

/**
 * @file   GPIO_Config
 * @brief  IO����������
 * @param  ��
 * @retval ��
 */
void IO_CTRL_Config(void)
{
  // ����һ��GPIO_InitTypeDef ���͵Ľṹ��
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIO������ʱ��

  /*D3*/
  GPIO_InitStructure.GPIO_Pin = CHG_POWER_EN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB_PORT, &GPIO_InitStructure);
  CHG_POWER_EN_ONOFF(0);

  //		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  //    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻����ʾ�ر�jtag��ʹ��swd��

  GPIO_InitStructure.GPIO_Pin = DSG_POWER_EN;       // ѡ��Ҫ�õ�GPIO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // ��������ģʽΪ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ���������ٶ�Ϊ50MHZ
  GPIO_Init(GPIOB_PORT, &GPIO_InitStructure);       // ���ÿ⺯������ʼ��GPIO
  DSG_POWER_EN_ONOFF(0);

  GPIO_InitStructure.GPIO_Pin = DISPLAY_POWER_EN;   // ѡ��Ҫ�õ�GPIO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // ��������ģʽΪ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ���������ٶ�Ϊ50MHZ
  GPIO_Init(GPIOB_PORT, &GPIO_InitStructure);       // ���ÿ⺯������ʼ��GPIO
  DISPLAY_POWER_EN_ONOFF(0);
}
