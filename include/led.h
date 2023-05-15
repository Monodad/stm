#ifndef __LED_H
#define __LED_H

#define LED5 5

#define LED5_GPIO_RCC RCC_APB2Periph_GPIOB
#define LED5_GPIO_PORT GPIOB
#define LED5_GPIO_PIN GPIO_Pin_0
#define LED5_ONOFF(x) GPIO_WriteBit(LED5_GPIO_PORT, LED5_GPIO_PIN, x);
void LED_GPIO_Config(void);
void LEDXToggle(uint8_t ledx);
#endif
