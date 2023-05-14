#ifndef __TIMER_H
#define __TIMER_H
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

void TIM2_Config(uint16_t arr, uint16_t psc);
void TIM3_Config(uint16_t arr, uint16_t psc);
void Timer_2Nvic_Config(void);
void Timer_3Nvic_Config(void);
void TIM2_IRQHandler(void);
#endif
