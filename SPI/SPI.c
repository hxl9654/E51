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
	功能描述:SPI通信模块
	备注:仅适用于带有SPI功能的STC15系列单片机
*////////////////////////////////////////////////////////////////////////////////////////
#include<STC15W4K.h>
#include<SPI.h>
bit IS_Master = 0;
sbit SS = P1^2;

void DataResive(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Send
*函数功能：SPI发送一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年5月18日
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Send(unsigned char dat)
{
    if(IS_Master == 1)
    {
        SS = 0;
		SPDAT = dat;
    }
    else SPDAT = dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：Interrupt_SPI
*函数功能：SPI中断函数
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年5月18日
*////////////////////////////////////////////////////////////////////////////////////
void Interrupt_SPI() interrupt 9
{
	SPSTAT = 0xB0;
	if(IS_Master == 1)
    {
		SS = 1;
		SS = 0;
		DataResive(SPDAT);
    }
    else
		DataResive(SPDAT);
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Init
*函数功能：SPI发送一位unsigned char 型的数据
*参数列表：
*   cpha
*       参数类型：bit型数据
*       参数描述：SPI CPHA参数值
*   cpol
*       参数类型：bit型数据
*       参数描述：SPI CPOL参数值
*   mode
*       参数类型：bit型数据
*       参数描述：SPI 主从模式设置（1：主模式，0：从模式）
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年5月18日
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Init(bit cpha, bit cpol, bit mode)
{
	if(mode == 1)
    {
        SPCTL = 0xD0;
        IS_Master = 1;
    }
	else
		SPCTL = 0x40;
	if(cpol == 1)
		SPCTL |= 0x08;
	if(cpha == 1)
		SPCTL |= 0x04;
	EA = 1;
	IE2 |= 0x02;
}
