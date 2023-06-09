/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：timer.c
 * 描述    ：通用定时器2中断初始化
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2016-04-08
 * 硬件连接: 无
 * 调试方式：J-Link-OB
 ********************************************************************************/
// 头文件

#include "wdg.h"
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "BQ76930.h"
// 通用定时器3中断初始化
// 这里时钟选择为APB1的2倍，而APB1为36M
// arr：自动重装值。
// psc：时钟预分频数
// 这里使用的是定时器3!
// extern uint8_t close;
// extern uint8_t open;
uint8_t cnt1 = 0;
uint8_t cnt2 = 0;
uint8_t open, close;
/**
 * @file   TimerNvic_Config
 * @brief  中断优先级NVIC设置
 * @param  无
 * @retval 无
 */
void TimerNvic_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // 设置中断组为2
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           // 中断事件为TIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 响应优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 允许中断
  NVIC_Init(&NVIC_InitStructure);                           // 根据指定参数初始化中断寄存器

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // 中断事件为TIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 响应优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 允许中断
  NVIC_Init(&NVIC_InitStructure);                           // 根据指定参数初始化中断寄存器
  //	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  //	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		//中断事件为TIM2
  //    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	//抢占优先级0
  //    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;      //响应优先级1
  //    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //允许中断
  //    NVIC_Init(&NVIC_InitStructure);                         //根据指定参数初始化中断寄存器
}
/**
 * @file   TIM2_Config
 * @brief  初始化定时器2
 * @param
 *					arr：自动重装值。
 *					psc：时钟预分频数
 * @retval 无
 */
void TIM2_Config(uint16_t arr, uint16_t psc)
{
  // 定时器定时时间T计算公式：T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // 定义一个定时器结构体变量
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 时钟使能
  TIM_DeInit(TIM2);                                    // 将IM2定时器初始化位复位值
  TIM_InternalClockConfig(TIM2);                       // 配置 TIM2 内部时钟
  // 定时器TIM2初始化
  TIM_TimeBaseStructure.TIM_Period = arr;                     // 设置自动重载寄存器值为最大值	0~65535之间
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // 自定义预分频系数，提供给定时器的时钟0~65535之间
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             // 根据指定参数初始化TIM时间基数寄存器
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);                       // 清中断，以免一启用中断后立即产生中断
  TIM_ARRPreloadConfig(TIM2, DISABLE);                        // 禁止ARR 预装载缓冲器

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM2中断源
  TIM_Cmd(TIM2, ENABLE);
  TimerNvic_Config();
}

void TIM3_Config(uint16_t arr, uint16_t psc)
{
  // 定时器定时时间T计算公式：T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // 定义一个定时器结构体变量
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 时钟使能
  TIM_DeInit(TIM3);                                    // 将IM2定时器初始化位复位值
  TIM_InternalClockConfig(TIM3);                       // 配置 TIM2 内部时钟
  // 定时器TIM2初始化
  TIM_TimeBaseStructure.TIM_Period = arr;                     // 设置自动重载寄存器值为最大值	0~65535之间
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // 自定义预分频系数，提供给定时器的时钟0~65535之间
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             // 根据指定参数初始化TIM时间基数寄存器
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);                       // 清中断，以免一启用中断后立即产生中断
  TIM_ARRPreloadConfig(TIM3, DISABLE);                        // 禁止ARR 预装载缓冲器

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能TIM3中断源
  TIM_Cmd(TIM3, ENABLE);                     // 关闭TIM2
}

void TIM4_Config(uint16_t arr, uint16_t psc)
{
  // 定时器定时时间T计算公式：T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;       // 定义一个定时器结构体变量
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 时钟使能
  TIM_DeInit(TIM4);                                    // 将IM2定时器初始化位复位值
  TIM_InternalClockConfig(TIM4);                       // 配置 TIM2 内部时钟
  // 定时器TIM2初始化
  TIM_TimeBaseStructure.TIM_Period = arr;                     // 设置自动重载寄存器值为最大值	0~65535之间
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // 自定义预分频系数，提供给定时器的时钟0~65535之间
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             // 根据指定参数初始化TIM时间基数寄存器
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);                       // 清中断，以免一启用中断后立即产生中断
  TIM_ARRPreloadConfig(TIM4, DISABLE);                        // 禁止ARR 预装载缓冲器

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // 使能TIM2中断源
  TIM_Cmd(TIM4, ENABLE);                     // 关闭TIM2
}
/**
 * @file   TIM2_IRQHandler
 * @brief  定时器2中断处理函数
 * @param  无
 * @retval 无
 */

// int cnt;
// void TIM3_IRQHandler(void)   //TIM3中断
//{
//   if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
//	{
//	  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
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

// void TIM4_IRQHandler(void)   //TIM3中断
//{
//	 TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx更新中断标志
//     if(close==1)
//		 {             JDQ_ONOFF(1);
//			              LED1_ONOFF(0);
//			              cnt1++;
//			  if(cnt1==20)
//				          {
//
//			              LED1_ONOFF(1);							//以0.5秒得周期闪烁
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
//		         LED2_ONOFF(1);							//以0.5秒得周期闪烁
//  			              cnt2=0;
//					          open=0;
//				}
//		 }
//
// }
//
