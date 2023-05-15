#ifndef __IO_CTRL_H
#define __IO_CTRL_H
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

#define GPIOB_RCC RCC_APB2Periph_GPIOB
#define GPIOB_PORT GPIOB
#define CHG_POWER_EN GPIO8
#define CHG_POWER_EN_ONOFF(x) GPIO_WriteBit(GPIOB_PORT, CHG_POWER_EN, x);

#define GPIOB_RCC RCC_APB2Periph_GPIOB
#define GPIOB_PORT GPIOB
#define DSG_POWER_EN GPIO9
#define DSG_POWER_EN_ONOFF(x) GPIO_WriteBit(GPIOB_PORT, DSG_POWER_EN, x);

#define GPIOB_RCC RCC_APB2Periph_GPIOB
#define GPIOB_PORT GPIOB
#define DISPLAY_POWER_EN GPIO10
#define DISPLAY_POWER_EN_ONOFF(x) GPIO_WriteBit(GPIOB_PORT, DISPLAY_POWER_EN, x);

void IO_CTRL_Config(void);

#endif
