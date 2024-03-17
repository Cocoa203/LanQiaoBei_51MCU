#include <STC15F2K60S2.H>
#include "iic.h"

float PCF8591_AD(unsigned char channel)
{
	float AD_data;
	unsigned char command,temp;
	if(channel==0){command=0x00;}
	if(channel==1){command=0x01;}
	if(channel==2){command=0x02;}
	if(channel==3){command=0x03;}
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(command);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp=IIC_RecByte();
	IIC_SendAck(0x01);
	IIC_Stop();
	AD_data=temp/255.0*5;
	return AD_data;
}

void PCF8591_DA(float DA_value)
{
	unsigned char DA_data;
	DA_data=(unsigned char)(DA_value/5.0*255);
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x40);
	IIC_WaitAck();
	IIC_SendByte(DA_value);
	IIC_WaitAck();
	IIC_Stop();
}