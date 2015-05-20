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

	文件名：UART.h
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：串口字符串通信模块-头文件
	备注：尽量使用封装好的函数进行操作，而不要使用直接对串口进行操作。
        使用该模块，请在config.h中定义UART_BUFF_MAX常量为数据缓存数组最大长度。
            如 #define UART_BUFF_MAX 64
        使用该模块，请在config.h中定义XTAL常量为晶振频率（单位：兆赫兹）。
            如 #define XTAL 11.059200
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_UART_
#define _HEAD_UART_

#include<intrins.h>
#include<config.h>
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_Conf
*函数功能：配置串口
*参数列表：
*   baud
*       参数类型：unsigned char型数据
*       参数描述：要设置的波特率
*////////////////////////////////////////////////////////////////////////////////////
void UART_Conf(unsigned int baud);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_SendString
*函数功能：向串口发送一个字符串
*参数列表：
*   *dat
*       参数类型：unsigned char型指针
*       参数描述：要发送的字符串的首地址
*   len
*       参数类型：unsigned char型数据
*       参数描述：要发送的字符串的长度
*////////////////////////////////////////////////////////////////////////////////////
void UART_SendString(unsigned char *dat,unsigned char len);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_RxMonitor
*函数功能：串口字符串接收结束判断，在定时器0中断函数中调用
*参数列表：
*   ms
*       参数类型：unsigned char型数据
*       参数描述：定时器延时时长（单位：ms）
*////////////////////////////////////////////////////////////////////////////////////
void UART_RxMonitor(unsigned char ms);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_Driver
*函数功能：串口通信监控函数，在主循环中调用。
*           如果接收到字符串，会自动调用另行编写的UART_Action(unsigned char *dat,unsigned char len)
*////////////////////////////////////////////////////////////////////////////////////
void UART_Driver();


#endif // _HEAD_UART_
