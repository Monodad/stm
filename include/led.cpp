/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：led.c
 * 描述    ：LED灯引脚配置
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2016-04-08
 * 硬件连接: D1->PC13;D2->PB0;D3->PB1
 * 调试方式：J-Link-OB
 **********************************************************************************/

// 头文件
#include "led.h"
#include "SYSTICK.h"
/**
 * @file   LED_GPIO_Config
 * @brief  LED灯引脚配置
 * @param  无
 * @retval 无
 */
void LED_GPIO_Config(void)
{
  // 定义一个GPIO_InitTypeDef 类型的结构体
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIO的外设时钟
  /*D1*/

  /*D5*/
  GPIO_InitStructure.GPIO_Pin = LED5_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @file   LEDXToggle
 * @brief  LED亮灭翻转
 * @param  ledx:1--PC13;2--PB0;3--PB1
 * @retval 无
 */
void LEDXToggle(uint8_t ledx)
{
  if (ledx == 5)
  {
    LED5_GPIO_PORT->ODR ^= LED5_GPIO_PIN;
  }
}
