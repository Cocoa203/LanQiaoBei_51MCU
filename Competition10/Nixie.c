#include <STC15F2K60S2.H>

unsigned char code P_NixieTab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0x7f,0x7f,0xc1,0x8e};
unsigned char NixieBuf[8]={10,10,10,10,10,10,10,10};
unsigned char PoitLoc;

void Nixie(unsigned char location,unsigned char show_num)
{
	if(show_num==11)
	{
		PoitLoc=location;
	}
	else if(show_num==12)
	{
		PoitLoc=0;
	}
	else
	{
		if(location==1){NixieBuf[location-1]=show_num;}
		if(location==2){NixieBuf[location-1]=show_num;}
		if(location==3){NixieBuf[location-1]=show_num;}
		if(location==4){NixieBuf[location-1]=show_num;}
		if(location==5){NixieBuf[location-1]=show_num;}
		if(location==6){NixieBuf[location-1]=show_num;}
		if(location==7){NixieBuf[location-1]=show_num;}
		if(location==8){NixieBuf[location-1]=show_num;}
	}
}

void NixieScan()
{
	static unsigned char i;
	i%=8;
	P2&=0x1f;
	P0=0x00;   //防止影响LED工作
	P2|=0xc0;
	if(i==0){P00=1;}
	if(i==1){P01=1;}
	if(i==2){P02=1;}
	if(i==3){P03=1;}
	if(i==4){P04=1;}
	if(i==5){P05=1;}
	if(i==6){P06=1;}
	if(i==7){P07=1;}
	P2&=0x1f;
	P2|=0xe0;
	if(i+1==PoitLoc)
	{
		P0=P_NixieTab[NixieBuf[i]]&0x7f;
	}
	else
	{
		P0=P_NixieTab[NixieBuf[i]];
	}
	P2&=0x1f;
	P0=0xff;
	i++;
}

void NixieOff()
{
	static unsigned char i;
	i%=8;
	P2&=0x1f;
	P0=0x00;   //防止影响LED工作
	P2|=0xc0;
	if(i==0){P00=1;}
	if(i==1){P01=1;}
	if(i==2){P02=1;}
	if(i==3){P03=1;}
	if(i==4){P04=1;}
	if(i==5){P05=1;}
	if(i==6){P06=1;}
	if(i==7){P07=1;}
	P2&=0x1f;
	P2|=0xe0;
	P0=0xff;
	P2&=0x1f;
	P0=0xff;
	i++;
}