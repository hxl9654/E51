#include<reg52.h>
#include<PCF8591.h>
#include<UART.h>
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

int main()
{
	unsigned char channel = 0, dat;
	unsigned char temp[20]={0};
	UART_Conf(9600);
	temp[0] = 'C';
	temp[1] = 'h';
	temp[2] = 'a';
	temp[3] = 'n';
	temp[4] = 'n';
	temp[5] = 'e';
	temp[6] = 'l';
	temp[8] = ':';
	temp[9] = ' ';
	temp[13] = '\n';
	while(1)
	{
		dat = PCF8591_Read(channel);		
		temp[7] = channel + '0';		
		temp[10] = dat / 100 + '0';
		temp[11] = dat / 10 % 10 + '0';
		temp[12] = dat % 10 + '0';
		if(channel == 3)
		{
			PCF8591_DA(dat);
			channel = 0;
		}
		else channel ++;
		UART_SendString(temp, 14);	
		Delay100ms();		
	}
	
}