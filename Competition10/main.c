#include <STC15F2K60S2.H>
#include "Key.h"
#include "Timer.h"
#include "Nixie.h"
#include "PCF8591.h"
#include "NE555N.h"

unsigned char AD_Flag,DA_Mode,LED_Mode=1,Measure_Mode,Nixie_Mode=1;

unsigned long Power(unsigned int num,unsigned char x)
{
	unsigned long result=1;
	while(x--)
	{
		result*=num;
	}
	return result;
}

void main()
{
	unsigned char key_num,temp,i,j;
	unsigned int AD_data;
	unsigned long frequency;
	float AD_value;
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		key_num=Key();
		if(key_num==4)
		{
			Measure_Mode++;
			Measure_Mode%=2;
		}
		if(key_num==5)
		{
			DA_Mode++;
			DA_Mode%=2;
		}
		if(key_num==6)
		{
			LED_Mode++;
			LED_Mode%=2;
		}
		if(key_num==7)
		{
			Nixie_Mode++;
			Nixie_Mode%=2;
		}

		//AD、DA模块
		if(Measure_Mode==0)
		{
			ET0=0;
			if(AD_Flag)
		{
			AD_Flag=0;
			AD_value=PCF8591_AD(3);
		}
		AD_data=AD_value*100;
		Nixie(1,13);
		Nixie(6,AD_data/100%10);
		Nixie(6,11);
		Nixie(7,AD_data/10%10);
		Nixie(8,AD_data%10);
		Nixie(2,10);
		Nixie(3,10);
		Nixie(4,10);
		Nixie(5,10);
		if(DA_Mode)
		{
			PCF8591_DA(AD_value);
		}
		else
		{
			PCF8591_DA(2.0);
		}
		}
		//频率测量模块
		if(Measure_Mode==1)
		{
			ET0=1;
			frequency=NE555N();
			Nixie(1,14);
			Nixie(2,10);
			Nixie(6,12);
			for(i=1;i<7;i++)
			{
				temp=frequency/(100000/Power(10,i-1));
				if(temp)
					break;
			}
			for(j=2+i;j<=8;j++)
				Nixie(j,frequency/(100000/(Power(10,j-3)))%10);
			for(j=2+i-1;j>2;j--)
				Nixie(j,10);
		}
		
		//LED模块
		if(LED_Mode)
		{
			if(Measure_Mode==0)
			{
				P0=0xff;
				P2&=0x1f;
				P2|=0x80;
				P00=0;P01=1;
				if(AD_value<1.5||(AD_value>=2.5&&AD_value<3.5))
				{
					P02=1;
				}
				else
				{
					P02=0;
				}
				
				if(DA_Mode)
				{
					P04=0;
				}
				else
				{
					P04=1;
				}
				P2&=0x1f;
			}
			if(Measure_Mode==1)
			{
				P0=0xff;
				P2&=0x1f;
				P2|=0x80;
				P00=1;P01=0;
				if(frequency<1000||(frequency>=5000&&frequency<10000))
				{
					P03=1;
				}
				else
				{
					P03=0;
				}
				P2&=0x1f;
			}
		}
		else
		{
			P0=0xff;
			P2&=0x1f;
			P2|=0x80;
			P2&=0x1f;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	NE555N_Count++;
}

void Timer1_Routine() interrupt 3
{
	
	static unsigned int i,j;
	i++;
	j++;
	if(i%2==0)
	{
		if(Nixie_Mode)
			NixieScan();
		else
			NixieOff();
	}
	if(i>=200)
	{
		i=0;
		AD_Flag=1;
	}
	if(j>=1000)
	{
		j=0;
		NE555N_Flag=1;
	}
}
	