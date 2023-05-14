/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��timer.c
 * ����    ��ͨ�ö�ʱ��2�жϳ�ʼ��
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-04-08
 * Ӳ������: ��
 * ���Է�ʽ��J-Link-OB
 ********************************************************************************/
// ͷ�ļ�

#include "wdg.h"
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "BQ76930.h"
// ͨ�ö�ʱ��3�жϳ�ʼ��
// ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
// arr���Զ���װֵ��
// psc��ʱ��Ԥ��Ƶ��
// ����ʹ�õ��Ƕ�ʱ��3!
// extern u8 close;
// extern u8 open;
u8 cnt1 = 0;
u8 cnt2 = 0;
u8 open, close;

/**
 * @file   TimerNvic_Config
 * @brief  �ж����ȼ�NVIC����
 * @param  ��
 * @retval ��
 */
void TimerNvic_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // �����ж���Ϊ2
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           // �ж��¼�ΪTIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // ��Ӧ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // �����ж�
  NVIC_Init(&NVIC_InitStructure);                           // ����ָ��������ʼ���жϼĴ���

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // �ж��¼�ΪTIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // ��Ӧ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // �����ж�
  NVIC_Init(&NVIC_InitStructure);                           // ����ָ��������ʼ���жϼĴ���

  //	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  //	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		//�ж��¼�ΪTIM2
  //    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	//��ռ���ȼ�0
  //    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;      //��Ӧ���ȼ�1
  //    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //�����ж�
  //    NVIC_Init(&NVIC_InitStructure);                         //����ָ��������ʼ���жϼĴ���
}
/**
 * @file   TIM2_Config
 * @brief  ��ʼ����ʱ��2
 * @param
 *					arr���Զ���װֵ��
 *					psc��ʱ��Ԥ��Ƶ��
 * @retval ��
 */
void TIM2_Config(u16 arr, u16 psc)
{
  // ��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // ����һ����ʱ���ṹ�����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ʱ��ʹ��
  TIM_DeInit(TIM2);                                    // ��IM2��ʱ����ʼ��λ��λֵ
  TIM_InternalClockConfig(TIM2);                       // ���� TIM2 �ڲ�ʱ��
  // ��ʱ��TIM2��ʼ��
  TIM_TimeBaseStructure.TIM_Period = arr;                     // �����Զ����ؼĴ���ֵΪ���ֵ	0~65535֮��
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // �Զ���Ԥ��Ƶϵ�����ṩ����ʱ����ʱ��0~65535֮��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // ����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             // ����ָ��������ʼ��TIMʱ������Ĵ���
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);                       // ���жϣ�����һ�����жϺ����������ж�
  TIM_ARRPreloadConfig(TIM2, DISABLE);                        // ��ֹARR Ԥװ�ػ�����

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ʹ��TIM2�ж�Դ
  TIM_Cmd(TIM2, ENABLE);
  TimerNvic_Config();
}

void TIM3_Config(u16 arr, u16 psc)
{
  // ��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // ����һ����ʱ���ṹ�����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // ʱ��ʹ��
  TIM_DeInit(TIM3);                                    // ��IM2��ʱ����ʼ��λ��λֵ
  TIM_InternalClockConfig(TIM3);                       // ���� TIM2 �ڲ�ʱ��
  // ��ʱ��TIM2��ʼ��
  TIM_TimeBaseStructure.TIM_Period = arr;                     // �����Զ����ؼĴ���ֵΪ���ֵ	0~65535֮��
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // �Զ���Ԥ��Ƶϵ�����ṩ����ʱ����ʱ��0~65535֮��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // ����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             // ����ָ��������ʼ��TIMʱ������Ĵ���
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);                       // ���жϣ�����һ�����жϺ����������ж�
  TIM_ARRPreloadConfig(TIM3, DISABLE);                        // ��ֹARR Ԥװ�ػ�����

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // ʹ��TIM3�ж�Դ
  TIM_Cmd(TIM3, ENABLE);                     // �ر�TIM2
}

void TIM4_Config(u16 arr, u16 psc)
{
  // ��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // ����һ����ʱ���ṹ�����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // ʱ��ʹ��
  TIM_DeInit(TIM4);                                    // ��IM2��ʱ����ʼ��λ��λֵ
  TIM_InternalClockConfig(TIM4);                       // ���� TIM2 �ڲ�ʱ��
  // ��ʱ��TIM2��ʼ��
  TIM_TimeBaseStructure.TIM_Period = arr;                     // �����Զ����ؼĴ���ֵΪ���ֵ	0~65535֮��
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // �Զ���Ԥ��Ƶϵ�����ṩ����ʱ����ʱ��0~65535֮��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // ����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             // ����ָ��������ʼ��TIMʱ������Ĵ���
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);                       // ���жϣ�����һ�����жϺ����������ж�
  TIM_ARRPreloadConfig(TIM4, DISABLE);                        // ��ֹARR Ԥװ�ػ�����

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // ʹ��TIM2�ж�Դ
  TIM_Cmd(TIM4, ENABLE);                     // �ر�TIM2
}
/**
 * @file   TIM2_IRQHandler
 * @brief  ��ʱ��2�жϴ�����
 * @param  ��
 * @retval ��
 */

// int cnt;
// void TIM3_IRQHandler(void)   //TIM3�ж�
//{
//   if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
//	{
//	  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־
//         cnt++;
//          	if(cnt == 20)
//			  {
//			    SHIP_ALL_DEVICE();
//			   }
//          if(cnt == 40)
//			  {
//			    WAKE_ALL_DEVICE();
//           cnt = 0;
//			   }
//	}
// }

// void TIM4_IRQHandler(void)   //TIM3�ж�
//{
//	 TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx�����жϱ�־
//     if(close==1)
//		 {             JDQ_ONOFF(1);
//			              LED1_ONOFF(0);
//			              cnt1++;
//			  if(cnt1==20)
//				          {
//
//			              LED1_ONOFF(1);							//��0.5���������˸
//  			              cnt1=0;
//										close=0;
//				           }
//		 }
//		 if(open==1)
//		 {
//			      JDQ_ONOFF(0);
//			      LED2_ONOFF(0);
//			      cnt2++;
//			 if(cnt2==20)
//		    {
//
//		         LED2_ONOFF(1);							//��0.5���������˸
//  			              cnt2=0;
//					          open=0;
//				}
//		 }
//
// }
//
