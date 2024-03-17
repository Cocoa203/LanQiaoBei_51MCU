/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 20

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit I2C_SDA = P2^1;  /* 数据线 */
sbit I2C_SCL = P2^0;  /* 时钟线 */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//总线启动条件
void IIC_Start(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SDA = 0;
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答
void IIC_SendAck(unsigned char ackbit)
{
    I2C_SCL = 0;
    I2C_SDA = ackbit;  					// 0：应答，1：非应答
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 0; 
    I2C_SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
unsigned char IIC_WaitAck(void)
{
    unsigned char ackbit;
	
    I2C_SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = I2C_SDA;
    I2C_SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        I2C_SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) I2C_SDA  = 1;
        else I2C_SDA  = 0;
        IIC_Delay(DELAY_TIME);
        I2C_SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    I2C_SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	I2C_SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(I2C_SDA) da |= 1;
	I2C_SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}
