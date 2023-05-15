#ifndef SYSTICK_H
#define SYSTICK_H
#include <libopencm3/cm3/systick.h>
void systick_Init(void);
void delay_ms(uint32_t ms);

#endif
