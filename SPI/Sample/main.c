/*//////////////////////////GPL开源许可证////////////////////////////////////////////////
    Copyright (C) <2015>  <Xianglong He>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    文件名:SPI_Analog.c
	作者:何相龙
	邮箱:qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述:SPI通信模块-Sample程序
	备注:该程序在IAP15W4K58S4单片机上进行测试
		 本程序的效果是，SPI主从机分别将接收到的数据加1后发送
*////////////////////////////////////////////////////////////////////////////////////////
#include<STC15W4K.h>
#include<SPI.h>
#define SPI_MODE 1
bit DataFlag = 0;
unsigned char DataResived = 0x00;
//该程序需要用到两片STC15单片机，将其中一片设置为主机，另一片为从机
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

int main()
{
	unsigned char dat = 0x00;
	#if SPI_MODE
		SPI_Init(0,0,1);
		SPI_Send(0x00);
		Delay10us();
		SPI_Read();
	#else
		SPI_Init(0,0,0);
	#endif

	while(1)
	{
		if(DataFlag)
		{
			DataFlag = 0;
			if(DataResived ==0xFE)DataResived +=2;
			else DataResived ++;
			SPI_Send(DataResived);
		}
	}
}
void DataResive(unsigned char dat)
{
	DataFlag = 1;
	DataResived = dat;
}