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

    文件名：SPI_Analog.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：SPI通信的IO口模拟实现
	备注：如使用的单片机自带SPI通信相关硬件功能（如STC15W系列），推荐直接使用其硬件模块。
          使用该模块，请在config.h中定义SPI_CS_SET常量为SPI总线的CS使能接口。
          如 #define SPI_CS_SET P0^0
          使用该模块，请在config.h中定义SPI_SCLK_SET常量为SPI总线的SCLK时钟信号接口。
          如 #define SPI_SCLK_SET P0^1
          使用该模块，请在config.h中定义SPI_MOSI_SET常量为SPI总线的MOSI信号接口。
          如 #define SPI_MOSI_SET P0^2
          使用该模块，请在config.h中定义SPI_MISO_SET常量为SPI总线的MISO信号接口。
          如 #define SPI_MISO_SET P0^3
*////////////////////////////////////////////////////////////////////////////////////////\

/*//////////////////外部声明//////////////////////////////////
extern void SPI_Init();		//SPI初始化（仅主模式使用）
extern void SPI_Write(uint8 dat);	//SPI主模式发送数据（dat：要发送的数据）
extern uint8 SPI_Read();	//SPI主模式读取数据，返回读取到的数据
extern void SPI_Slave_Send(uint8 dat);	//SPI从模式回应数据（dat：要回应的数据）
extern uint8 SPI_Slave_Resive();	//SPI从模式接收数据，返回接收到的数据
////////////////////////////////////////////////////////////*/
//2015年1月8日
#include<reg52.h>
#include<intrins.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

#define CPOL 1	  //设置SPI通信模式（建议：如果要用SPI做多机通信，不想作死的话，建议CPHA=1）
#define CPHA 1
#define Dealy(); {_nop_();_nop_();_nop_();_nop_();_nop_();}	//根据实际延时要求修改
sbit CS=P1^3;	//SPI通信的四个IO口
sbit SCLK=P1^1;
sbit MOSI=P1^0;
sbit MISO=P1^2;

void SPI_Init()
{
	SCLK=CPOL;
	CS=1;
}
void SPI_Write(uint8 dat)
{
	uint8 mask;
	CS=0;
	if(CPHA)
		{
			for(mask=0x80;mask!=0;mask>>=1)
				{
					SCLK=~SCLK;
					MOSI=dat&mask;
					Dealy();
					SCLK=~SCLK;
					Dealy();
				}
		}
	else
		{
			for(mask=0x80;mask!=0;)
				{
					MOSI=dat&mask;
					SCLK=~SCLK;
					Dealy();
					mask>>=1;
					SCLK=~SCLK;
					Dealy();
				}
		}
	CS=1;
}
uint8 SPI_Read()
{
	uint8 dat=0,mask=0x80;
	CS=0;
		if(CPHA)
		{
			for(;mask!=0;mask>>=1)
				{
					SCLK=~SCLK;
					Dealy();
					if(MISO)dat|=mask;
					SCLK=~SCLK;
					Dealy();
				}
		}
	else
		{
	        for(;mask!=0;mask>>=1)
		        {
					Dealy();
					if(MISO)dat|=mask;
					SCLK=~SCLK;
					Dealy();
		            SCLK=~SCLK;
					Dealy();
		        }
	    }
	CS=1;
	return dat;
}
void SPI_Slave_Send(uint8 dat)
{
	uint8 mask=0x80;
	if(CPHA)
		{
			while(CS);
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					MISO=dat&mask;
					while(SCLK!=CPOL);
				}
		}
	else
		{
			for(;mask!=0;mask>>=1)
				{
					MISO=dat&mask;
					while(CS);
					while(SCLK==CPOL);
					while(SCLK!=CPOL);
				}
		}

}
uint8 SPI_Slave_Resive()
{
	uint8 mask=0x80,dat=0;
	while(CS);
	if(CPHA)
		{
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					while(SCLK!=CPOL);
					if(MOSI)dat|=mask;
				}
		}
	else
		{
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					if(MOSI)dat|=mask;
					while(SCLK!=CPOL);
				}
		}
   return dat;
}
