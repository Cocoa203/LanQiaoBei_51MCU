#ifndef _IIC_H
#define _IIC_H

void IIC_Start(void); 
void IIC_Stop(void);  
unsigned char IIC_WaitAck(void);  
void IIC_SendAck(unsigned char ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

#endif