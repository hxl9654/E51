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
	功能描述:SPI通信模块-头文件
	备注:仅适用于带有SPI功能的STC15系列单片机
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_SPI_
#define _HEAD_SPI_

#include<intrins.h>
#include<config.h>
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Read
*函数功能：SPI主机模式：读取一位unsigned char型数据
*备注：读取到数据后，会调用用户自行编写的DataResive函数。从机模式下，此函数不可用——从机收到数据会自动调用DataResive函数。
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Read();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Send
*函数功能：SPI发送一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Send(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Init
*函数功能：SPI中断函数
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
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Init(bit cpha, bit cpol, bit mode);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Close
*函数功能：关闭SPI
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Close();
#endif
