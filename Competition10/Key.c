#include <STC15F2K60S2.H>
#include "Delay.h"

unsigned char Key()
{
	unsigned char key_num=0;
	P30=1;P31=1;P32=1;P33=1;
	if(P30==0){Delay(15);while(P30==0);Delay(15);key_num=7;}
	if(P31==0){Delay(15);while(P31==0);Delay(15);key_num=6;}
	if(P32==0){Delay(15);while(P32==0);Delay(15);key_num=5;}
	if(P33==0){Delay(15);while(P33==0);Delay(15);key_num=4;}
	return key_num;
}
