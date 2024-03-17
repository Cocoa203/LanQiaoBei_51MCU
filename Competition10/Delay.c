#include <intrins.h>

void Delay(unsigned int xms)		//@12.000MHz
{
	while(xms--)
	{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
	}
}
