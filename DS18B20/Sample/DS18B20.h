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

	文件名：DS18B20.h
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：DS18B20温度传感器的简单操作函数模块的头文件
	备注：尽量使用封装好的函数进行操作，而不要使用直接对DS18B20读写的函数。
          使用该模块，请在config.h中定义DS18B20_IO_SET常量为DS18B20的数据接口。
          如 #define DS18B20_IO_SET P0^0
          使用该模块，请在config.h中定义STC_YX常量为STC单片机指令集名称。
          如 #define STC_YX "STC_Y5"
          使用该模块，请在config.h中定义XTAL常量为晶振频率
          如 #define XTAL 11.059200
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_DS18B20_
#define _HEAD_DS18B20_

#include<intrins.h>
#include<config.h>

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_GetTemp
*函数功能：读取DS18B20，获得温度。
*参数列表：
*   *addr
*       参数类型：unsigned char型指针（连续8个unsigned char的数据）
*       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00
*返回值：一个double型变量，获取到的温度值。（发生错误时，返回-999）
*////////////////////////////////////////////////////////////////////////////////////
double DS18B20_GetTemp(unsigned char *addr);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Start
*函数功能：启动18B20温度转换。
*参数列表：
*   *addr
*       参数类型：unsigned char型指针（连续8个unsigned char的数据）
*       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00
*返回值：一个bit型变量，启动是否正常（1；正常，0：失败）
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Start(unsigned char *addr);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Init
*函数功能：初始化18B20
*返回值：一个bit型变量，初始化是否正常（1；正常，0：失败）
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Init();
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Write  （尽量不要直接调用）
*函数功能：向18B20写一个unsigned char型的数据或命令
*参数列表：
*   dat
*       参数类型：unsigned char型整数
*       参数描述：要写入的数据或命令
*////////////////////////////////////////////////////////////////////////////////////
void DS18B20_Write(unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Read   尽量不要直接调用）
*函数功能：从DS18B20中读取一位数据
*返回值：一个unsigned char型变量，读取到的数据
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS18B20_Read();

#endif // _HEAD_DS18B20_


