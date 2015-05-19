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

    文件名：SPI_Analog.h
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：SPI通信的IO口模拟实现-头文件
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
#ifndef _HEAD_SPI_Analog_
#define _HEAD_SPI_Analog_

#include<intrins.h>
#include<config.h>

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Init
*函数功能：SPI初始化（仅主模式使用）
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Init();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Write
*函数功能：SPI从模式：发送一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Write(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Read
*函数功能：SPI主模式：读取一位unsigned char 型的数据
*返回值：一个unsigned char型数据，读取到的数据。
*////////////////////////////////////////////////////////////////////////////////////
unsigned char SPI_Read();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Slave_Send
*函数功能：SPI从模式：回应一位unsigned char 型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要回复的数据
*////////////////////////////////////////////////////////////////////////////////////
void SPI_Slave_Send(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：SPI_Slave_Resive
*函数功能：SPI从模式：接收一位unsigned char 型的数据
*返回值：一个unsigned char型数据，接收到的数据。
*////////////////////////////////////////////////////////////////////////////////////
unsigned char SPI_Slave_Resive();
#endif // _HEAD_SPI_Analog_
