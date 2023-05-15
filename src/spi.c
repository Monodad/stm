#include "spi.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ALIENTEKս��STM32������
// SPI���� ����
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// �޸�����:2012/9/9
// �汾��V1.0
// ��Ȩ���У�����ؾ���
// Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

// ������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25Q64/NRF24L01
// SPI�ڳ�ʼ��
// �������Ƕ�SPI1�ĳ�ʼ��
#define GPIO_Pin GPIOA // ����SPI cs�ź���PB12
#define GPIO_Speed GPIO_Speed_50MHz
#define GPIO_Mode GPIO_Mode_Out_PP
void SPI1_Init(void)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// SPI_InitTypeDef SPI_InitStructure;
	rcc_periph_clock_enable(RCC_SPI1);
	rcc_periph_clock_enable(GPIOA);

	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
	gpio_set_mode(GPIO_BANK_SPI1_MISO, GPIO_MODE_INPUT, GPIO_CNF_OUTPUT_PUSHPULL, GPIO_SPI1_MISO);
	gpio_set_mode(GPIO_BANK_SPI1_MOSI, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_SPI1_MOSI);
	gpio_set_mode(GPIO_BANK_SPI1_SCK, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_SPI1_SCK);
	// GPIO_InitStructure.GPIO_Pin = GPIO5 | GPIO6 | GPIO7;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // PB13/14/15�����������
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(GPIOA, &GPIO_InitStructure); // ��ʼ��GPIOB
	gpio_get(GPIOA, GPIO5 | GPIO6 | GPIO7);
	// GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7); // PB13/14/15����

	// SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // ����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	spi_set_full_duplex_mode(SPI1);
	// SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // ����SPI����ģʽ:����Ϊ��SPI
	spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_256, SPI_CR1_CPOL, SPI_CR1_CPHA, SPI_CR1_DFF_8BIT, SPI_CR1_LSBFIRST);
	// SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					 // ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	// SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;							 // ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	// SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						 // ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	// SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							 // NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	// SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	// SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					 // ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	// SPI_InitStructure.SPI_CRCPolynomial = 7;							 // CRCֵ����Ķ���ʽ
	// SPI_Init(SPI1, &SPI_InitStructure);									 // ����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	spi_set_master_mode(SPI1);
	spi_enable_crc(SPI1);
	spi_enable(SPI1); // ʹ��SPI����

	spi_send(SPI1, 0xff); // ��������
}
// SPI �ٶ����ú���
// SpeedSet:
// SPI_BaudRatePrescaler_2   2��Ƶ
// SPI_BaudRatePrescaler_8   8��Ƶ
// SPI_BaudRatePrescaler_16  16��Ƶ
// SPI_BaudRatePrescaler_256 256��Ƶ
void spi_setup(void)
{
	gpio_set_mode(GPIO_BANK_SPI1_MISO, GPIO_MODE_INPUT, GPIO_CNF_OUTPUT_PUSHPULL, GPIO_SPI1_MISO);
	gpio_set_mode(GPIO_BANK_SPI1_MOSI, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_SPI1_MOSI);
	gpio_set_mode(GPIO_BANK_SPI1_SCK, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_SPI1_SCK);
	spi_disable(SPI1);
	spi_reset(SPI1);
	spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_64, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
	spi_enable(SPI1);
}
// void SPI1_SetSpeed(uint8_t SPI_BaudRatePrescaler)
// {
// 	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
// 	SPI1->CR1 &= 0XFFC7;
// 	SPI1->CR1 |= SPI_BaudRatePrescaler; // ����SPI1�ٶ�
// 	SPI_Cmd(SPI1, ENABLE);
// }

// SPIx ��дһ���ֽ�
// TxData:Ҫд����ֽ�
// ����ֵ:��ȡ�����ֽ�
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
	uint8_t retry = 0;
	while (SPI_SR(SPI1) != SPI_SR_TXE) // ���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	spi_send(SPI1, TxData); // ͨ������SPIx����һ������
	retry = 0;

	while (SPI_SR(SPI1) != SPI_SR_RXNE) // ���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	return spi_read(SPI1); // ����ͨ��SPIx������յ�����
}
