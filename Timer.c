#include <STC15F2K60S2.H>

void Timer0_Init()
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x04;
	TL0 = 0xff;				//设置定时初始值
	TH0 = 0xff;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;					//定时器0开始计时
	ET0=0;
	EA=1;
}

void Timer1_Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0x18;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1=1;
	EA=1;
}
