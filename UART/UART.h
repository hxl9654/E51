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
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_UART_
#define _HEAD_UART_

#include<intrins.h>
#include<config.h>
void UART_RxMonitor(uint8 ms)//UART字符串接收结束判断。在定时器中调用（ms：定时器时钟周期）
void UART_Driver()//UART通信监控函数，在主循环中调用。如果接收到字符串，会自动调用另行编写的UART_Action(uint8 *dat,uint8 len)
void UART_SendString(uint8 *dat,uint8 len)  //串口通信：发送一个字符串（dat：要发送的字符串，len：字符串长度）
void UART_Conf(uint16 baud) //UART设置函数（buad：欲设置的波特率）
#endif // _HEAD_UART_
