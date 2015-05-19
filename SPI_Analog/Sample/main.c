#include<reg52.h>
#include<SPI_Analog.h>
#define SPI_MODE 0
sfr AUXR = 0x8E;
void UartInit(void)		
{
	SCON = 0x50;		
	AUXR |= 0x40;		
	AUXR &= 0xFE;		
	TMOD &= 0x0F;		
	TL1 = 0xF9;		
	TH1 = 0xFF;		
	ET1 = 0;		
	TR1 = 1;	
}

int main()
{
	unsigned char dat = 0x96;
	UartInit();
	#if SPI_MODE
		SPI_Master_Init();
	#endif
	while(1)
	{
		#if SPI_MODE
			SPI_Write(dat);
			dat = SPI_Read();
			dat ++;
			if(dat == 0xFF)dat ++;
		#else 					
			dat = SPI_Slave_Resive();			
			dat ++;
			//if(dat == 0xFF)dat ++;	
			SPI_Slave_Send(dat);	
			//SBUF = dat;		
		#endif
	}
}