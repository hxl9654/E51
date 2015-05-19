/*//////////////////////////GPL开源许可证////////////////////////////////////////////////
    Copyright (C) <2014>  <Xianglong He>
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

	文件名：IIC_Analog.h
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：用单片机IO口模拟实现IIC通信-头文件
	备注：使用该模块，请在config.h中定义IIC_SDA_SET常量为IIC总线的SDA数据接口。
          如 #define IIC_SDA_SET P0^0
          使用该模块，请在config.h中定义IIC_SCL_SET常量为IIC总线的SCL数据接口。
          如 #define IIC_SCL_SET P0^1
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_IIC_Analog_
#define _HEAD_IIC_Analog_

#include<intrins.h>
#include<config.h>

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Start
*函数功能：发送IIC总线起始信号
*////////////////////////////////////////////////////////////////////////////////////
void IIC_Start();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Stop
*函数功能：发送IIC总线停止信号
*////////////////////////////////////////////////////////////////////////////////////
void IIC_Stop();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Write
*函数功能：向IIC总线发送一个unsigned char型数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*返回值：一个bit型数，是否正常完成操作（1：正常，0：异常）
*////////////////////////////////////////////////////////////////////////////////////
bit IIC_Write(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Read
*函数功能：从IIC总线读取一个unsigned char型数据
*参数列表：
*   ACK
*       参数类型：bit型数据
*       参数描述：数据读取结束后发送的应答位或非应答位
*返回值：一个unsigned char型变量，读取到的数据
*////////////////////////////////////////////////////////////////////////////////////
unsigned char IIC_Read(bit ACK);

#endif // _HEAD_IIC_
