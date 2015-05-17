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
          使用该模块，请在config.h中定义SPI_CPOL_SET常量为SPI通信的CPOL模式。
          如 #define SPI_CPOL_SET 1
          使用该模块，请在config.h中定义SPI_CPOL_SET常量为SPI通信的CPHA模式。
          建议：如果要用SPI做多机通信，建议设置CPHA为1，这样可以提高本程序的稳定性。
          如 #define SPI_CPHA_SET 1
          使用该模块，请在config.h中定义SPI_CS_SET常量为SPI总线的CS使能接口。
          如 #define SPI_CS_SET P0^0
          使用该模块，请在config.h中定义SPI_SCLK_SET常量为SPI总线的SCLK时钟信号接口。
          如 #define SPI_SCLK_SET P0^1
          使用该模块，请在config.h中定义SPI_MOSI_SET常量为SPI总线的MOSI信号接口。
          如 #define SPI_MOSI_SET P0^2
          使用该模块，请在config.h中定义SPI_MISO_SET常量为SPI总线的MISO信号接口。
          如 #define SPI_MISO_SET P0^3
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg52.h>
#include<SPI_Analog.h>

#define Dealy(); {_nop_();_nop_();_nop_();_nop_();_nop_();}	//SPI通信的小延时

#define CPOL SPI_CPOL_SET
#define CPHA SPI_CPHA_SET
//设置SPI通信的参数

sbit CS = SPI_CS_SET;	//定义SPI通信的四个IO口
sbit SCLK = SPI_SCLK_SET;
sbit MOSI = SPI_MOSI_SET;
sbit MISO = SPI_MISO_SET;

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Init
*函数功能：SPI初始化（仅主模式使用）
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年1月8日
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Init()
{
	SCLK = CPOL;
	CS = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Write
*函数功能：SPI从模式：发送一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年1月8日
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Write(unsigned char dat)
{
	unsigned char mask;
	CS = 0;
	if(CPHA)
		{
			for(mask = 0x80; mask != 0; mask >>= 1)
				{
					SCLK = ~ SCLK;
					MOSI = dat & mask;
					Dealy();
					SCLK = ~ SCLK;
					Dealy();
				}
		}
	else
		{
			for(mask = 0x80; mask != 0;)
				{
					MOSI = dat&mask;
					SCLK = ~ SCLK;
					Dealy();
					mask >>= 1;
					SCLK = ~ SCLK;
					Dealy();
				}
		}
	CS = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Read
*函数功能：SPI主模式：读取一位unsigned char 型的数据
*参数列表：
*   无
*返回值：一个unsigned char型数据，读取到的数据。
*版本：1.0
*作者：何相龙
*日期：2015年1月8日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char SPI_Read()
{
	unsigned char dat = 0,mask = 0x80;
	CS = 0;
		if(CPHA)
		{
			for(;mask != 0;mask >>= 1)
				{
					SCLK = ~ SCLK;
					Dealy();
					if(MISO)dat |= mask;
					SCLK = ~ SCLK;
					Dealy();
				}
		}
	else
		{
	        for(;mask != 0;mask >>= 1)
		        {
					Dealy();
					if(MISO)dat |= mask;
					SCLK = ~ SCLK;
					Dealy();
		            SCLK = ~ SCLK;
					Dealy();
		        }
	    }
	CS = 1;
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Slave_Send
*函数功能：SPI从模式：回应一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要回复的数据
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年1月8日
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Slave_Send(unsigned char dat)
{
	unsigned char mask=0x80;
	if(CPHA)
		{
			while(CS);
			for(;mask != 0;mask >>= 1)
				{
					while(SCLK == CPOL);
					MISO = dat&mask;
					while(SCLK != CPOL);
				}
		}
	else
		{
			for(;mask != 0;mask >>= 1)
				{
					MISO = dat & mask;
					while(CS);
					while(SCLK == CPOL);
					while(SCLK != CPOL);
				}
		}

}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Slave_Resive
*函数功能：SPI从模式：接收一位unsigned char 型的数据
*参数列表：
*   无
*返回值：一个unsigned char型数据，接收到的数据。
*版本：1.0
*作者：何相龙
*日期：2015年1月8日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char SPI_Slave_Resive()
{
	unsigned char mask = 0x80,dat = 0;
	while(CS);                              //等待SPI使能信号
	if(CPHA)
		{
			for(;mask != 0;mask >>= 1)
				{
					while(SCLK == CPOL);    //
					while(SCLK != CPOL);
					if(MOSI)dat |= mask;
				}
		}
	else
		{
			for(;mask != 0;mask >>= 1)
				{
					while(SCLK == CPOL);
					if(MOSI)dat |= mask;
					while(SCLK != CPOL);
				}
		}
   return dat;
}
