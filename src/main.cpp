/******************** (C) BOBO   ********************************
 * 文件名  ：main.c
 * 描述    ：主要是完成BMS相关检测和保护
 * 库版本  ：V3.50
 * 作者    ：BOBO
 * 版本更新: 2019-04-12
 * 调试方式：J-Link
 **********************************************************************************/

// 头文件
#include "main.h"
#include "usart.h"
#include "usart2.h"
#include "BQ76930.h"
#include "IO_CTRL.h"
#include <stdio.h>
#include "math.h"
#include "timer.h"
#include "can.h"
#include "LTC6804-1.h"
#include "spi.h"
#include "adc.h"
#include "SYSTICK.h"

extern unsigned char ucUSART1_ReceiveDataBuffer[];
unsigned char BMS_DATA_FLAG;

uint16_t cell_codes[15][12];   // 调用adcvax和rdcv后，电池电压存在这个数组中
unsigned int cell_voltage[50]; // 这个数组用来显示电池电压的
unsigned char cell_zu = 15;    // 一共几组电池
unsigned char shang[500] = {0xAA, 0x01};
unsigned char shang1[50] = {0xAA, 0x02};
unsigned char shang2[50] = {0xAA, 0x03};
unsigned char shang3[50] = {0xAA, 0x04};

unsigned char can_buf1[8] = {0xAA, 0x01};
unsigned char can_buf2[8] = {0xAA, 0x02};
unsigned char can_buf3[8] = {0xAA, 0x03};
unsigned char can_buf4[8] = {0xAA, 0x04};
unsigned char can_buf5[8] = {0xAA, 0x05};
unsigned char can_buf6[8] = {0xAA, 0x06};
unsigned char can_buf7[8] = {0xAA, 0x07};
extern int Batt[50];
void Get_Update_ALL_Data(void)
{
    int Sum_val;
    Sum_val = cell_voltage[0] + cell_voltage[1] + cell_voltage[2] + cell_voltage[3] + cell_voltage[4] + cell_voltage[5] + cell_voltage[6] + cell_voltage[7] + cell_voltage[8] + cell_voltage[9] + cell_voltage[10] + cell_voltage[11];
    //}

    cell_voltage[12] = Sum_val;

    shang[32] = (char)(cell_voltage[12] >> 8);
    shang[33] = (char)(cell_voltage[12] & 0XFF);

    shang2[14] = (char)shang[32];
    shang2[15] = (char)shang[33];

    can_buf6[2] = (char)shang[32];
    can_buf6[3] = (char)shang[33];
}

int SOC;
void Get_SOC(void)
{

    if (cell_voltage[12] > (4100 * 9))
    {
        SOC = 100;
    }
    else if ((cell_voltage[12] > (4100 * 9)) && (cell_voltage[12] < (4150 * 9)))
    {
        SOC = 95;
    }
    else if ((cell_voltage[12] > (4050 * 9)) && (cell_voltage[12] < (4100 * 9)))
    {
        SOC = 90;
    }
    else if ((cell_voltage[12] > (4000 * 9)) && (cell_voltage[12] < (4050 * 9)))
    {
        SOC = 88;
    }
    else if ((cell_voltage[12] > (3950 * 9)) && (cell_voltage[12] < (4000 * 9)))
    {
        SOC = 87;
    }
    else if ((cell_voltage[12] > (3900 * 9)) && (cell_voltage[12] < (3950 * 9)))
    {
        SOC = 86;
    }
    else if ((cell_voltage[12] > (3900 * 9)) && (cell_voltage[12] < (3950 * 9)))
    {
        SOC = 85;
    }
    else if ((cell_voltage[12] > (3850 * 9)) && (cell_voltage[12] < (3900 * 9)))
    {
        SOC = 84;
    }
    else if ((cell_voltage[12] > (3800 * 9)) && (cell_voltage[12] < (3850 * 9)))
    {
        SOC = 83;
    }
    else if ((cell_voltage[12] > (3750 * 9)) && (cell_voltage[12] < (3800 * 9)))
    {
        SOC = 82;
    }
    else if ((cell_voltage[12] > (3700 * 9)) && (cell_voltage[12] < (3750 * 9)))
    {
        SOC = 81;
    }
    else if ((cell_voltage[12] > (3650 * 9)) && (cell_voltage[12] < (3700 * 9)))
    {
        SOC = 80;
    }
    else if ((cell_voltage[12] > (3600 * 9)) && (cell_voltage[12] < (3650 * 9)))
    {
        SOC = 79;
    }
    else if ((cell_voltage[12] > (3550 * 9)) && (cell_voltage[12] < (3600 * 9)))
    {
        SOC = 78;
    }
    else if ((cell_voltage[12] > (3500 * 9)) && (cell_voltage[12] < (3550 * 9)))
    {
        SOC = 77;
    }

    else if ((cell_voltage[12] > (3450 * 9)) && (cell_voltage[12] < (3500 * 9)))
    {
        SOC = 40;
    }
    else if ((cell_voltage[12] > (3400 * 9)) && (cell_voltage[12] < (3500 * 9)))
    {
        SOC = 30;
    }
    else if ((cell_voltage[12] > (3300 * 9)) && (cell_voltage[12] < (3400 * 9)))
    {
        SOC = 20;
    }
    else if ((cell_voltage[12] > (3200 * 9)) && (cell_voltage[12] < (3300 * 9)))
    {
        SOC = 10;
    }
    else if ((cell_voltage[12] > (3100 * 9)) && (cell_voltage[12] < (3200 * 9)))
    {
        SOC = 5;
    }
    cell_voltage[13] = SOC;

    shang[34] = (char)(cell_voltage[13] >> 8);
    shang[35] = (char)(cell_voltage[13] & 0XFF);

    shang2[16] = (char)shang[34];
    shang2[17] = (char)shang[35];

    can_buf6[4] = (char)shang[34];
    can_buf6[5] = (char)shang[35];
}

void Get_BQ_Current(void)
{
    if (Batt[2] > 1351)
    {
        Batt[2] = (Batt[2] - 1349) * 100 / 2;
        //		Batt[2]=0;
    }
    else if (Batt[2] < 1346)
    {
        Batt[2] = (1349 - Batt[2]) * 100 / 2;
    }
    else
    {
        Batt[2] = 0;
    }
    //	if((Batt[2]>60000)||(Batt[2]<0)){Batt[2]=0;}
    shang[36] = Batt[2] >> 8;
    shang[37] = Batt[2] & 0X00FF;
    shang2[18] = shang[36];
    shang2[19] = shang[37];

    can_buf6[6] = (char)shang[36];
    can_buf6[7] = (char)shang[37];
}

// void Get_T1(void)
// {
//     shang[38] = Batt[0];
//     shang3[2] = shang[38];
//     can_buf7[2] = (char)shang[38];
// }
// unsigned char BMS_sta, DSG_STA, CHG_STA, DSG_STA_FLAG, CHG_STA_FLAG;
// void BMS_STA(void)
// {
//     DSG_STA = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9);
//     CHG_STA = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8);
//     shang[39] = DSG_STA;
//     shang[40] = CHG_STA;

//     can_buf7[3] = (char)shang[39];
//     can_buf7[4] = (char)shang[40];
// }
// void Only_Open_CHG(void)
// {
//     CHG_POWER_EN_ONOFF(1);
// }
// void Only_Close_CHG(void)
// {
//     CHG_POWER_EN_ONOFF(0);
// }

// void Only_Open_DSG(void)
// {
//     DSG_POWER_EN_ONOFF(1);
// }
// void Only_Close_DSG(void)
// {
//     DSG_POWER_EN_ONOFF(0);
// }

// void Open_DSG_CHG(void)
// {
//     CHG_POWER_EN_ONOFF(1);
//     DSG_POWER_EN_ONOFF(1);
// }
// void Close_DSG_CHG(void)
// {
//     CHG_POWER_EN_ONOFF(0);
//     DSG_POWER_EN_ONOFF(0);
// }

void Get_Cell_Voltage(void)
{
    int vi;
    for (vi = 0; vi < 12; vi++)
    {
        cell_voltage[vi] = cell_codes[0][vi] / 10;

        shang[vi + 2 + vi] = (char)(cell_voltage[vi] >> 8);
        shang[vi + 3 + vi] = (char)(cell_voltage[vi] & 0X00FF);
    }
}

unsigned int Max, Min;
void Get_Cell_Voltage_Max_Min(void)
{
    int i;

    Max = cell_voltage[0];
    Min = cell_voltage[0];
    for (i = 1; i < 10; i++)
    {
        if (cell_voltage[i] > Max)
        {
            Max = cell_voltage[i];
        }
        if (cell_voltage[i] > 0)
        {
            if (cell_voltage[i] < Min)
            {
                Min = cell_voltage[i];
            }
        }
    }
    shang[41] = (char)(Max >> 8);
    shang[42] = (char)(Max & 0x00FF);

    shang[43] = (char)(Min >> 8);
    shang[44] = (char)(Min & 0x00FF);
}

int main(void)
{
    int UV_FLAG = 0, OV_FLAG = 0;

    SYSTICK_Init(); // 系统初始化，时钟配置；
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    // NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    IO_CTRL_Config(); // 系统的一些IO口设置；
    delay_ms(100);
    LTC6804_initialize(); // LTC6804初始化配置；
    delay_ms(1000);

    // TIM2_Config(99, 7199);                                                    // 100mS定时器中断
    // CAN_Mode_Init(CAN_SJW_1tq, CAN_BS2_8tq, CAN_BS1_9tq, 4, CAN_Mode_Normal); // CAN初始化环回模式,波特率500Kbps
    // Adc_Init();                                                               // 温度，电流ADC测量；
    // UartSend("MODE_CFG(1);DIR(1);FSIMG(2097152,0,0,220,176,0);\r\n");
    delay_ms(1000);

    while (1)
    {
        LTC6804_adcvax();                     // 6804初始化
        LTC6804_rdcv(0, cell_zu, cell_codes); // 6804获取12节电池电压
        // show();                               // 数据更新并上传上位机，屏，蓝牙

        if (Max > 4200) // 电池最大电压大于4200mv
        {
            Only_Close_CHG(); // 关闭充电MOS管
            OV_FLAG = 1;
        }
        if (OV_FLAG == 1) // 过压状态
        {
            if (Max < 4100) // 电池最大电压小于4100mv
            {
                Only_Open_CHG(); // 打开充电MOS管
                OV_FLAG = 0;
            }
        }
        if (Min < 2800) // 电池最小电压低于4200mv
        {
            Only_Close_DSG(); // 关闭放电MOS管
            UV_FLAG = 1;
        }
        if (UV_FLAG == 1) // 欠压状态
        {
            if (Min > 3000) // 电池最小电压大于3000mv
            {
                Only_Open_DSG(); // 打开放电MOS管
                UV_FLAG = 0;
            }
        }
        if (Batt[2] > 8000) // 如果电流大于2000ma，关闭充放电MOS管
        {
            Close_DSG_CHG();
        }
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
