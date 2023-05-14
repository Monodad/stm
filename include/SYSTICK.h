#ifndef __SYSTICK_H
#define __SYSTICK_H
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
void SYSTICK_Init(void);
void delay_ms(uint32_t ms);

#endif
