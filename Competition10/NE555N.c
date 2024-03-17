#include <STC15F2K60S2.H>

unsigned char NE555N_Flag;
unsigned long NE555N_Count;
unsigned long NE555N()
{
	static unsigned long frequency=5;
	if(NE555N_Flag)
	{
		NE555N_Flag=0;
		TR0=0;
		frequency=NE555N_Count;
		NE555N_Count=0;
		TR0=1;
	}
	return frequency;
}
