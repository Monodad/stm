#include "BQ76930.h"
#include "SYSTICK.h"

#include "i2c1.h"
#include "can.h"
#include "usart.h"
#include "math.h"
#include "string.h"
#include "IO_CTRL.h"
#include "usart2.h"
/*****************************
file:BQData.c
decription:
   1.�ɼ�BQ76930��14λADC�������ƫ�õ�ѹ:void get_offset(void)
   2.�ɼ������ѹ:void Get_Batteryx(void),����xȡֵ1-10��
   3.BQ76930��ʼ�� void BQ_config(void)
   4.��ȡBQ76930�Ĵ���ֵ�� void readbqstate(void)
   5.
******************************/
/***********************
fuction:void get_offset(void)
************************/
int ADC_offset, GAIN;
float ADC_GAIN = 0;

void Get_offset(void)
{
	unsigned char gain[2];

	gain[0] = IIC1_read_one_byte(ADCGAIN1);						  // ADC_GAIN1
	gain[1] = IIC1_read_one_byte(ADCGAIN2);						  // ADC_GAIN2
	ADC_GAIN = ((gain[0] & 0x0c) << 1) + ((gain[1] & 0xe0) >> 5); // 12uV
	ADC_offset = IIC1_read_one_byte(ADCOFFSET);					  // 45mV
	GAIN = 365 + ADC_GAIN;										  // GAIN=377uV
}
/****************************************
fuction: void Get_Battery1(void)
description:��ȡ��1�ŵ����ص�ѹ
Parameters:batterylval[0],battery1val[1];
******************************************/
void BQ76930_config(void)
{
	BQ_1_2_config();
	Get_offset();
	OV_UV_1_2_PROTECT();
	OCD_SCD_PROTECT();
}

void BQ_1_2_config(void)
{

	BQ_1_config(); //
}

void OV_UV_1_2_PROTECT(void)
{
	OV_UV_1_PROTECT();
}

void SHIP_ALL_DEVICE(void)
{
	IIC1_write_one_byte_CRC(SYS_STAT, 0xFF);
	SHIP_1_BQ769();
}

int Batteryval[50] = {0};
unsigned char shang[50] = {0xAA, 0x01};
unsigned char shang1[50] = {0xAA, 0x02};

unsigned char can_buf1[8] = {0xAA, 0x01};
unsigned char can_buf2[8] = {0xAA, 0x02};
unsigned char can_buf3[8] = {0xAA, 0x03};
unsigned char can_buf4[8] = {0xAA, 0x04};
unsigned char can_buf5[8] = {0xAA, 0x05};
unsigned char can_buf6[8] = {0xAA, 0x06};
unsigned char can_buf7[8] = {0xAA, 0x07};

void Get_Battery1(void)
{
	unsigned int readbattbuf[2];
	unsigned int battery1val[2];
	short batteryval1;

	readbattbuf[1] = IIC1_read_one_byte(0x0c);
	readbattbuf[0] = IIC1_read_one_byte(0x0d);

	batteryval1 = readbattbuf[1];
	batteryval1 = (batteryval1 << 8) | readbattbuf[0];
	batteryval1 = ((batteryval1 * GAIN) / 1000) + ADC_offset; // �����ѹ���㹫ʽ����1��
	Batteryval[0] = batteryval1;

	battery1val[1] = (char)(batteryval1 >> 8);
	battery1val[0] = (char)(batteryval1 & 0x00FF);

	shang[2] = battery1val[1];
	shang[3] = battery1val[0];

	can_buf1[2] = shang[2];
	can_buf1[3] = shang[3];

	// printf("%d\n",batteryval1);
}

/****************************************
fuction: void Get_Battery2(void)
description:��ȡ��2�ŵ����ص�ѹ
Parameters:battery2val[0],battery2val[1];
******************************************/
void Get_Battery2(void)
{

	char readbattbuf[2];
	int batteryval2;
	short battery2val[2];

	readbattbuf[1] = IIC1_read_one_byte(0x0e);
	readbattbuf[0] = IIC1_read_one_byte(0x0f);

	batteryval2 = readbattbuf[1];
	batteryval2 = (batteryval2 << 8) | readbattbuf[0];

	batteryval2 = ((batteryval2 * GAIN) / 1000) + ADC_offset; //????????,?2?
	Batteryval[1] = batteryval2;

	battery2val[1] = (char)(batteryval2 >> 8);
	battery2val[0] = (char)(batteryval2 & 0x00FF);

	shang[4] = battery2val[1];
	shang[5] = battery2val[0];
	can_buf1[4] = shang[4];
	can_buf1[5] = shang[5];
}
/****************************************
fuction: void Get_Battery3(void)
description:��ȡ��3�ŵ����ص�ѹ
Parameters:battery3val[0],battery3val[1];
******************************************/
void Get_Battery3(void)
{

	char readbattbuf[2];
	int batteryval3;
	char battery3val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x10);
	readbattbuf[0] = IIC1_read_one_byte(0x11);

	batteryval3 = readbattbuf[1];
	batteryval3 = (batteryval3 << 8) | readbattbuf[0];
	batteryval3 = ((batteryval3 * GAIN) / 1000) + ADC_offset; //????????,?3?
	Batteryval[2] = batteryval3;
	battery3val[1] = (char)(batteryval3 >> 8);
	battery3val[0] = (char)(batteryval3 >> 0);
	shang[6] = battery3val[1];
	shang[7] = battery3val[0];

	can_buf1[6] = shang[6];
	can_buf1[7] = shang[7];
}
/****************************************
fuction: void Get_Battery4(void)
description:��ȡ��4�ŵ����ص�ѹ
Parameters:battery4val[0],battery4val[1];
******************************************/
void Get_Battery4(void)
{
	char readbattbuf[2];
	int batteryval4;
	char battery4val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x12);
	readbattbuf[0] = IIC1_read_one_byte(0x13);

	batteryval4 = readbattbuf[1];
	batteryval4 = (batteryval4 << 8) | readbattbuf[0];
	batteryval4 = ((batteryval4 * GAIN) / 1000) + ADC_offset; //????????,?4?
	Batteryval[3] = batteryval4;
	battery4val[1] = (char)(batteryval4 >> 8);
	battery4val[0] = (char)(batteryval4 >> 0);
	shang[8] = battery4val[1];
	shang[9] = battery4val[0];
	can_buf2[2] = shang[8];
	can_buf2[3] = shang[9];
}
/****************************************
fuction: void Get_Battery5(void)
description:��ȡ��5�ŵ����ص�ѹ
Parameters:battery5val[0],battery5val[1];
******************************************/
void Get_Battery5(void)
{
	char readbattbuf[2];
	short batteryval5;
	char battery5val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x14);
	readbattbuf[0] = IIC1_read_one_byte(0x15);

	batteryval5 = readbattbuf[1];
	batteryval5 = (batteryval5 << 8) | readbattbuf[0];
	batteryval5 = ((batteryval5 * GAIN) / 1000) + ADC_offset; //????????,?5?
	Batteryval[4] = batteryval5;
	battery5val[1] = (char)(batteryval5 >> 8);
	battery5val[0] = (char)(batteryval5 & 0x00FF);

	shang[10] = battery5val[1];
	shang[11] = battery5val[0];

	can_buf2[4] = shang[10];
	can_buf2[5] = shang[11];
}
/****************************************
fuction: void Get_Battery6(void)
description:��ȡ��6�ŵ����ص�ѹ
Parameters:battery6val[0],battery6val[1];
******************************************/
void Get_Battery6(void)
{

	char readbattbuf[2];
	short batteryval6;
	char battery6val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x16);
	readbattbuf[0] = IIC1_read_one_byte(0x17);

	batteryval6 = readbattbuf[1];
	batteryval6 = (batteryval6 << 8) | readbattbuf[0];
	batteryval6 = ((batteryval6 * GAIN) / 1000) + ADC_offset; //????????,?6?
	Batteryval[5] = batteryval6;
	battery6val[1] = (char)(batteryval6 >> 8);
	battery6val[0] = (char)(batteryval6 & 0x00FF);

	shang[12] = battery6val[1];
	shang[13] = battery6val[0];

	can_buf2[6] = shang[12];
	can_buf2[7] = shang[13];
}
/****************************************
fuction: void Get_Battery7(void)
description:��ȡ��7�ŵ����ص�ѹ
Parameters:battery7val[0],battery7val[1];
******************************************/
void Get_Battery7(void)
{
	char readbattbuf[2];
	short batteryval7;
	char battery7val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x18);
	readbattbuf[0] = IIC1_read_one_byte(0x19);

	batteryval7 = readbattbuf[1];
	batteryval7 = (batteryval7 << 8) | readbattbuf[0];
	batteryval7 = ((batteryval7 * GAIN) / 1000) + ADC_offset; //????????,?7?
	Batteryval[6] = batteryval7;
	battery7val[1] = (char)(batteryval7 >> 8);
	battery7val[0] = (char)(batteryval7 & 0x00FF);

	shang[14] = battery7val[1];
	shang[15] = battery7val[0];

	can_buf3[2] = shang[14];
	can_buf3[3] = shang[15];
}
/****************************************
fuction: void Get_Battery8(void)
description:��ȡ��8�ŵ����ص�ѹ
Parameters:battery8val[0],battery8val[1];
******************************************/
void Get_Battery8(void)
{
	char readbattbuf[2];
	int batteryval8;
	char battery8val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x1a);
	readbattbuf[0] = IIC1_read_one_byte(0x1b);

	batteryval8 = readbattbuf[1];
	batteryval8 = (batteryval8 << 8) | readbattbuf[0];
	batteryval8 = ((batteryval8 * GAIN) / 1000) + ADC_offset; //????????,?8?
	Batteryval[7] = batteryval8;
	battery8val[1] = (char)(batteryval8 >> 8);
	battery8val[0] = (char)(batteryval8 >> 0);
	shang[16] = battery8val[1];
	shang[17] = battery8val[0];

	can_buf3[4] = shang[16];
	can_buf3[5] = shang[17];
}

/****************************************
fuction: void Get_Battery9(void)
description:��ȡ��9�ŵ����ص�ѹ
Parameters:battery9val[0],battery9val[1];
******************************************/
void Get_Battery9(void)
{
	char readbattbuf[2];
	short batteryval9;
	char battery9val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x1c);
	readbattbuf[0] = IIC1_read_one_byte(0x1d);

	batteryval9 = readbattbuf[1];
	batteryval9 = (batteryval9 << 8) | readbattbuf[0];
	batteryval9 = ((batteryval9 * GAIN) / 1000) + ADC_offset; //????????,?8?

	Batteryval[8] = batteryval9;
	battery9val[1] = (char)(batteryval9 >> 8);
	battery9val[0] = (char)(batteryval9 & 0x00FF);
	// Batteryval[4]=batteryval9;

	shang[18] = battery9val[1];
	shang[19] = battery9val[0];
	can_buf3[6] = shang[18];
	can_buf3[7] = shang[19];
}
/****************************************
fuction: void Get_Battery10(void)
description:��ȡ��10�ŵ����ص�ѹ
Parameters:battery10val[0],battery10val[1];
******************************************/
void Get_Battery10(void)
{
	char readbattbuf[2];
	short batteryval10;
	char battery10val[2];
	readbattbuf[1] = IIC1_read_one_byte(0x1e);
	readbattbuf[0] = IIC1_read_one_byte(0x1f);

	batteryval10 = readbattbuf[1];
	batteryval10 = (batteryval10 << 8) | readbattbuf[0];
	batteryval10 = ((batteryval10 * GAIN) / 1000) + ADC_offset; //????????,?8?
	Batteryval[9] = batteryval10;
	battery10val[1] = (char)(batteryval10 >> 8);
	battery10val[0] = (char)(batteryval10 & 0x00FF);

	shang[20] = battery10val[1];
	shang[21] = battery10val[0];

	can_buf4[2] = shang[20];
	can_buf4[3] = shang[21];
	shang1[2] = battery10val[1];
	shang1[3] = battery10val[0];
}

/****************************************
/****************************
��ȡ���е�ص��ܵ�ѹֵ���ô���1��ӡ����
 *****************************/
float SOC;
void Get_Update_ALL_Data(void)
{
	int i, Sum_val = 0;
	for (i = 0; i < 10; i++)
	{
		Sum_val += Batteryval[i];
	}
	Batteryval[10] = Sum_val;

	shang[22] = (char)(Batteryval[10] >> 8);
	shang[23] = (char)(Batteryval[10] & 0XFF);

	can_buf6[2] = shang[22];
	can_buf6[3] = shang[23];
	shang1[4] = shang[22];
	shang1[5] = shang[23];
}

void Get_SOC(void)
{
	//		float a;
	//  a = (float)Batteryval[10];

	//  if(	Batteryval[10] >(4100*6))
	//       {SOC=100;}
	//	else if((	Batteryval[10] >(4100*6))&&(Batteryval[10]<(4150*6))){SOC=95;}
	//	else if((Batteryval[10]>(4050*6))&&(Batteryval[10]<(4100*6))){SOC=90;}
	//	else if((Batteryval[10]>(4000*6))&&(Batteryval[10]<(4050*6))){SOC=88;}
	//	else if((Batteryval[10]>(3950*6))&&(Batteryval[10]<(4000*6))){SOC=87;}
	//	else if((Batteryval[10]>(3900*6))&&(Batteryval[10]<(3950*6))){SOC=86;}
	//	else if((Batteryval[10]>(3900*6))&&(Batteryval[10]<(3950*6))){SOC=85;}
	//	else if((Batteryval[10]>(3850*6))&&(Batteryval[10]<(3900*6))){SOC=84;}
	//	else if((Batteryval[10]>(3800*6))&&(Batteryval[10]<(3850*6))){SOC=83;}
	//	else if((Batteryval[10]>(3750*6))&&(Batteryval[10]<(3800*6))){SOC=82;}
	//	else if((Batteryval[10]>(3700*6))&&(Batteryval[10]<(3750*6))){SOC=81;}
	//	else if((Batteryval[10]>(3650*6))&&(Batteryval[10]<(3700*6))){SOC=80;}
	//	else if((Batteryval[10]>(3600*6))&&(Batteryval[10]<(3650*6))){SOC=79;}
	//	else if((Batteryval[10]>(3550*6))&&(Batteryval[10]<(3600*6))){SOC=78;}
	//	else if((Batteryval[10]>(3500*6))&&(Batteryval[10]<(3550*6))){SOC=77;}
	//
	//	else if((Batteryval[10]>(3450*6))&&(Batteryval[10]<(3500*6))){SOC=40;}
	//	else if((Batteryval[10]>(3400*6))&&(Batteryval[10]<(3500*6))){SOC=30;}
	//	else if((Batteryval[10]>(3300*6))&&(Batteryval[10]<(3400*6))){SOC=20;}
	//	else if((Batteryval[10]>(3200*6))&&(Batteryval[10]<(3300*6))){SOC=10;}
	//	else if((Batteryval[10]>(3100*6))&&(Batteryval[10]<(3200*6))){SOC=5;}
	//	Batteryval[32] = SOC;

	//  shang[24]=(char)(Batteryval[32] >> 8);
	//  shang[25]=(char)(Batteryval[32] &0XFF);
	//	can_buf6[4]=shang[24];
	//	can_buf6[5]=shang[25];

	float SOC;

	SOC = (float)Batteryval[1];
	SOC = (SOC - 2800) / (4200 - 2800) * 100;
	Batteryval[32] = SOC;
	//	Batteryval[7] = SOC;
	shang[24] = (char)(Batteryval[32] >> 8);
	shang[25] = (char)(Batteryval[32] & 0XFF);
	shang1[6] = shang[24];
	shang1[7] = shang[25];
	can_buf6[4] = shang[24];
	can_buf6[5] = shang[25];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void OV_UV_1_PROTECT(void)
{
	unsigned char OVTrip_Val, UVTrip_Val;
	float t = 0.377;
	OVTrip_Val = (unsigned char)((((unsigned int)((OVPThreshold - ADC_offset) / t + 0.5)) >> 4) & 0xFF);
	UVTrip_Val = (unsigned char)((((unsigned int)((UVPThreshold - ADC_offset) / t + 0.5)) >> 4) & 0xFF);
	IIC1_write_one_byte_CRC(OV_TRIP, OVTrip_Val);
	IIC1_write_one_byte_CRC(UV_TRIP, UVTrip_Val);
}

void OCD_SCD_PROTECT(void)
{

	IIC1_write_one_byte_CRC(PROTECT1, 0x19); // ���ö�·����66A(SRN-SRP33mV)����·��ʱ400us��RSNS=0.
	IIC1_write_one_byte_CRC(PROTECT2, 0x7F); // ����OSDΪ100A(SRN-SRP50mV)����ʱ�����Ϊ1280ms��
}

/****************************************
fuction: void BQ_1_config(void)
description:BQ76930��ʼ��
Parameters: None
 //0x04�Ĵ���0x19��ӦSCD��ʱ70uS���ŵ��·��ѹ33mV��
 //0x05�Ĵ������ü�����Ϊ1-shotģʽ��
 //0x06�Ĵ���0x39��ӦOCD����ʱʱ��80mS���ŵ������ѹ33mV����·�͹�����Ӧ��������60A.
******************************************/
unsigned char BQ769_INITAdd[11] = {SYS_STAT, CELLBAL1, CELLBAL2, SYS_CTRL1, SYS_CTRL2, PROTECT1, PROTECT2, PROTECT3, OV_TRIP, UV_TRIP, CC_CFG};
unsigned char BQ769_INITdata[11] = {0xFF, 0x00, 0x00, 0x18, 0X43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19};
void BQ_1_config(void)
{
	char i;
	for (i = 0; i < 11; i++)
	{
		delay_ms(50);
		IIC1_write_one_byte_CRC(BQ769_INITAdd[i], BQ769_INITdata[i]);
	}
}

/****************************************
/****************************************
fuction:void SHIP_1_BQ769(void)
description:BQ76930����͹���ģʽ
Parameters: None
******************************************/
void SHIP_1_BQ769(void)
{
	IIC1_write_one_byte_CRC(SYS_CTRL1, 0x19); // 01
	delay_ms(20);
	IIC1_write_one_byte_CRC(SYS_CTRL1, 0x1a); // 10
}

/****************************************

 /****************************************
fuction: void Get_BQCurrent(void)
description:BQ76930�����������������谴4m��/8����
Parameters: None
******************************************/

void Get_BQ_Current(void)
{
	unsigned char readCurrentbuf[2];
	unsigned int Currentbufval;
	unsigned int Currentval;
	unsigned char Currentbuf[1];
	readCurrentbuf[1] = IIC1_read_one_byte(CC_HI_BYTE);
	readCurrentbuf[0] = IIC1_read_one_byte(CC_LO_BYTE);
	Currentbufval = (readCurrentbuf[1] << 8) + readCurrentbuf[0];

	if (Currentbufval <= 0x7D00)
	{

		Currentval = (Currentbufval * 2.11); // ��λmV����4m�����㣬��λmA��
		Batteryval[11] = Currentval;
		shang[26] = Currentval >> 8;
		shang[27] = Currentval & 0X00FF;
		can_buf6[6] = shang[26];
		can_buf6[7] = shang[27];
		shang1[8] = shang[26];
		shang1[9] = shang[27];
	}
	else
	{
		Currentval = ((0XFFFF - Currentbufval) * 2.11);
		Batteryval[11] = Currentval;
		shang[26] = Currentval >> 8;
		shang[27] = Currentval & 0X00FF;
		can_buf6[6] = shang[26];
		can_buf6[7] = shang[27];
		shang1[8] = shang[26];
		shang1[9] = shang[27];
	}
}
/****************************************
fuction: void Get_BQ_1_Temp(void)
description:BQ76930 103AT�¶Ȳ���
Parameters: None
******************************************/

float Tempval_2;

void Get_BQ1_2_Temp(void)
{
	float Rt = 0;
	float Rp = 10000;
	float T2 = 273.15 + 25;
	float Bx = 3380;
	float Ka = 273.15;
	unsigned char readTempbuf[2];
	int TempRes;
	unsigned char Tempbuf[1];
	readTempbuf[1] = IIC1_read_one_byte(TS2_HI_BYTE);
	readTempbuf[0] = IIC1_read_one_byte(TS2_LO_BYTE);
	TempRes = (readTempbuf[1] << 8) | readTempbuf[0];
	TempRes = (10000 * (TempRes * 382 / 1000)) / (3300 - (TempRes * 382 / 1000));
	Tempval_2 = 1 / (1 / T2 + (log(TempRes / Rp)) / Bx) - Ka + 0.5;
	Batteryval[12] = Tempval_2;
	shang[28] = Batteryval[12];

	can_buf7[2] = shang[28];
	shang1[10] = shang[28];
}

/****************************************
fuction: �����1��2��3��4��5��6��7��8��9��10�ֱ��ʾ������ϵ�1��10�ڵľ��⣬
		������Ҫע�����ڵĵ�ش�����ͬʱ�������⡣���ھ����������ͬ��Ҫ�û������Լ�����������
description:
Parameters: None
******************************************/
void Battery1_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL1, 0X01);
}

void Battery2_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL1, 0X02);
}
void Battery3_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL1, 0X04);
}
void Battery4_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL1, 0X10);
}
void Battery5_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X01);
}

void Battery6_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X02);
}

void Battery7_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X10);
}
void Battery8_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X04);
}
void Battery9_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X08);
}
void Battery10_Balance(void)
{
	IIC1_write_one_byte_CRC(CELLBAL2, 0X10);
}

void Balance_Stop(void)
{
	IIC1_write_one_byte_CRC(CELLBAL1, 0X00);
	IIC1_write_one_byte_CRC(CELLBAL2, 0X00);
}

void Balance_Start(char i)
{
	if (i == 0)
	{
		Battery1_Balance();
	}
	else if (i == 1)
	{
		Battery2_Balance();
	}
	else if (i == 2)
	{
		Battery3_Balance();
	}
	else if (i == 3)
	{
		Battery4_Balance();
	}
	else if (i == 4)
	{
		Battery5_Balance();
	}
	else if (i == 5)
	{
		Battery6_Balance();
	}
	else if (i == 6)
	{
		Battery7_Balance();
	}

	else if (i == 7)
	{
		IIC1_write_one_byte_CRC(CELLBAL2, 0X04);
	}

	else if (i == 8)
	{
		IIC1_write_one_byte_CRC(CELLBAL2, 0X08);
	}

	else if (i == 9)
	{
		IIC1_write_one_byte_CRC(CELLBAL2, 0X10);
	}
}

int imax, imin, imaxp, iminp;
void Cell_Battery_MAX_MIN(void)
{
	char i;
	imaxp = iminp = 0;
	imax = imin = Batteryval[0];
	for (i = 0; i < 10; i++)
	{
		if (Batteryval[i] > imax)
		{
			imax = Batteryval[i];
			imaxp = i;
		}
		if (Batteryval[i] < imin)
		{
			imin = Batteryval[i];
			iminp = i;
		}
	}
}

void Cell_Balance(int Difference)
{
	Cell_Battery_MAX_MIN();
	if ((imax - imin) > Difference)
	{
		Balance_Start(imaxp);
	}
	else
		Balance_Stop();
}

unsigned char BMS_sta, DSG_STA, CHG_STA, DSG_STA_FLAG, CHG_STA_FLAG;
void BMS_STA(void)
{
	BMS_sta = IIC1_read_one_byte(SYS_CTRL2);
	DSG_STA = BMS_sta & 0x02;
	CHG_STA = BMS_sta & 0x01;
	shang[29] = DSG_STA;
	shang[30] = CHG_STA;

	can_buf7[3] = shang[29];
	can_buf7[4] = shang[30];
}

void Only_Open_CHG(void)
{
	BMS_STA();
	if (DSG_STA != 0)
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X43);
	}
	else
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X41);
	}
}
void Only_Close_CHG(void)
{
	BMS_STA();
	if (DSG_STA != 0)
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X42);
	}
	else
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X40);
	}
}

void Only_Open_DSG(void)
{
	BMS_STA();
	if (CHG_STA != 0)
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X43);
	}
	else
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X42);
	}
}
void Only_Close_DSG(void)
{
	BMS_STA();
	if (CHG_STA != 0)
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X41);
	}
	else
	{
		IIC1_write_one_byte_CRC(SYS_CTRL2, 0X40);
	}
}

void Open_DSG_CHG(void)
{
	IIC1_write_one_byte_CRC(SYS_CTRL2, 0X43);
}
void Close_DSG_CHG(void)
{
	IIC1_write_one_byte_CRC(SYS_CTRL2, 0X40);
}
void Update_val(void)
{
	char NEW[50] = {0};
	int n;
	for (n = 0; n < 50; n++)

	{
		USART_SendData(USART1, shang[n]); // ����һ���ֽ�����
		delay_ms(10);
	}

	USART2_Printf(shang, 20, ASCII_CODE);
	delay_ms(200);
	USART2_Printf(shang1, 19, ASCII_CODE);

	Can_Send_Msg(can_buf1, 8, 0x0001);
	delay_ms(5);
	Can_Send_Msg(can_buf2, 8, 0x0002);
	delay_ms(5);
	Can_Send_Msg(can_buf3, 8, 0x0003);
	delay_ms(5);
	Can_Send_Msg(can_buf4, 8, 0x0004);
	delay_ms(5);
	Can_Send_Msg(can_buf5, 8, 0x0005);
	delay_ms(5);
	Can_Send_Msg(can_buf6, 8, 0x0006);
	delay_ms(5);
	Can_Send_Msg(can_buf7, 8, 0x0007);
	delay_ms(5);

	UartSend("CLR(61);\r\n");
	delay_ms(200);
	UartSend("CLR(61);\r\n");
	delay_ms(200);
	UartSend("DIR(1);\r\n");
	delay_ms(200);
	sprintf(NEW, "DCV16(0,0,'%s%d%s',3);\r\n", "��һ�ڵ�ѹ:", Batteryval[0], "mV");
	UartSend(NEW);

	delay_ms(200);

	sprintf(NEW, "DCV16(0,20,'%s%d%s',3);\r\n", "�ڶ��ڵ�ѹ:", Batteryval[1], "mV");
	UartSend(NEW);

	delay_ms(200);

	sprintf(NEW, "DCV16(0,40,'%s%d%s',3);\r\n", "�����ڵ�ѹ:", Batteryval[4], "mV");
	UartSend(NEW);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,60,'%s%d%s',3);\r\n", "���Ľڵ�ѹ:", Batteryval[5], "mV");
	UartSend(NEW);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,80,'%s%d%s',3);\r\n", "����ڵ�ѹ:", Batteryval[6], "mV");
	UartSend(NEW);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,100,'%s%d%s',3);\r\n", "�����ڵ�ѹ:", Batteryval[9], "mV");
	UartSend(NEW);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,120,'%s%d%s',3);\r\n", "�ܵ�ѹ:", Batteryval[10], "mV");

	UartSend(NEW);
	delay_ms(200);
	sprintf(NEW, "DCV16(0,140,'%s%d%s',3);\r\n", "���SOCΪ:", Batteryval[32], "%");
	UartSend(NEW);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,160,'%s%.2f%s',3);\r\n", "����¶�Ϊ:", Tempval_2, "��");
	UartSend(NEW);
	delay_ms(1000);
	UartSend("CLR(61);\r\n");
	delay_ms(200);

	delay_ms(200);
	sprintf(NEW, "DCV16(0,0,'%s%d%s',3);\r\n", "����:", Batteryval[11], "mA");
	UartSend(NEW);

	delay_ms(200);

	sprintf(NEW, "DCV24(0,20,'%s',3);\r\n", "");
	UartSend(NEW);

	delay_ms(100);
}
void Get_Update_Data(void)
{
	Get_Battery1();
	Get_Battery2();
	Get_Battery5();
	Get_Battery6();
	Get_Battery7();
	Get_Battery10();
	Get_Update_ALL_Data(); // �ܵ�ѹ
	Get_SOC();
	Get_BQ1_2_Temp();
	Get_BQ_Current();
	BMS_STA();
	Update_val();
}
int OT_Alarm_flag, UT_Alarm_flag;

/****************************************
fuction:void readbqstate(void)
description:��ȡ�����ź�ֵ
Parameters: UV_Alarm_flag�OOV_Alarm_flag
			SCD_Alarm_flag,OCD_Alarm_flag
******************************************/

int UV_Alarm_flag, OV_Alarm_flag, SCD_Alarm_flag, OCD_Alarm_flag;
void ALERT_1_Recognition(void)
{

	unsigned char sys_stat_1, sys_stat_2, UV_1, OV_1, UV_2, OV_2, SCD, OCD;
	sys_stat_1 = IIC1_read_one_byte(SYS_STAT); // ��ȡ״̬SYS_CTRL2

	UV_1 = sys_stat_1 & 0x08; // ȡ��UVλ
	OV_1 = sys_stat_1 & 0x04;
	SCD = sys_stat_1 & 0x02;
	OCD = sys_stat_1 & 0x01;
	if ((UV_1 == 0x08) || (UV_2 == 0x08))
	{
		UV_Alarm_flag = 1; // Ƿѹ����
		printf("pack UV\n");
	}
	else
		UV_Alarm_flag = 0; // û��Ƿѹ
	if ((OV_1 == 0x04) || (OV_2 == 0x04))
	{
		OV_Alarm_flag = 1;
		IIC1_write_one_byte_CRC(SYS_STAT, 0X80);
		printf("pack OV\n");
	}
	else
		OV_Alarm_flag = 0;
	if (SCD == 0x02)
	{
		SCD_Alarm_flag = 1;
		printf("pack SCD\n");
	}
	else
		SCD_Alarm_flag = 0;

	if (OCD == 0x01)
	{
		OCD_Alarm_flag = 1;
		printf("pack OCD\n");
	}
	else
		OCD_Alarm_flag = 0;
}

unsigned char CRC8(unsigned char *ptr, unsigned char len, unsigned char key)
{
	unsigned char i;
	unsigned char crc = 0;
	while (len-- != 0)
	{
		for (i = 0x80; i != 0; i /= 2)
		{
			if ((crc & 0x80) != 0)
			{
				crc *= 2;
				crc ^= key;
			}
			else
				crc *= 2;

			if ((*ptr & i) != 0)
				crc ^= key;
		}
		ptr++;
	}
	return (crc);
}
