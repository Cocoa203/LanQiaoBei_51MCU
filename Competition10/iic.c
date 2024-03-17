/*
  ����˵��: IIC������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include "reg52.h"
#include "intrins.h"

#define DELAY_TIME 20

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit I2C_SDA = P2^1;  /* ������ */
sbit I2C_SCL = P2^0;  /* ʱ���� */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//������������
void IIC_Start(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SDA = 0;
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//����Ӧ��
void IIC_SendAck(unsigned char ackbit)
{
    I2C_SCL = 0;
    I2C_SDA = ackbit;  					// 0��Ӧ��1����Ӧ��
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 1;
    IIC_Delay(DELAY_TIME);
    I2C_SCL = 0; 
    I2C_SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//�ȴ�Ӧ��
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

//ͨ��I2C���߷�������
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

//��I2C�����Ͻ�������
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
