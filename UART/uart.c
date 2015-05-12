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

	文件名：UART.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：串口字符串通信模块
	备注：尽量使用封装好的函数进行操作，而不要使用直接对串口进行操作。
*////////////////////////////////////////////////////////////////////////////////////////

	//2014年12月9日

#include<reg51.h>
#include<UART.h>

#ifndef BUFFMAX
#define BUFFMAX 64
#endif // 如果没有定义BUFFMAX，则默认为64

extern void UART_Action(unsigned char *dat, unsigned char len);
//此函数须另行编写：当串口完成一个字符串结束后会自动调用
unsigned char pdata UART_Buff[BUFFMAX];     //串口接收缓冲区
unsigned char UART_BuffIndex = 0;           //串口接收缓冲区当前位置
bit UART_SendFlag;                          //串口发送完成标志
bit UART_ResiveFlag;                        //串口接收完成标志
bit UART_ResiveStringEndFlag;               //串口字符串接收全部完成标志
bit UART_ResiveStringFlag;                  //串口字符串正在接收标志

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_Conf
*函数功能：配置串口
*参数列表：
*   baud
*       参数类型：unsigned char型数据
*       参数描述：要设置的波特率
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void UART_Conf(unsigned int baud) //UART设置函数（buad：欲设置的波特率）
{
	TL1 = TH1 = 256 - 11059200 / 12 / 32 / baud;
	EA = 1;
	ES = 1;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TR1 = 1;
}
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
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void UART_SendString(unsigned char *dat, unsigned char len)
{
	while(len)
	{
		len --;
		SBUF = *dat;
		dat ++;
		while(! UART_SendFlag);
		UART_SendFlag = 0;
	}
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_Driver
*函数功能：串口通信监控函数，在主循环中调用。
*           如果接收到字符串，会自动调用另行编写的UART_Action(unsigned char *dat,unsigned char len)
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void UART_Driver()//
{
	unsigned char pdata dat[BUFFMAX];
	unsigned char len;
	if(UART_ResiveStringEndFlag)
		{
			UART_ResiveStringEndFlag = 0;
			len = UART_Read(dat, BUFFMAX);
			UART_Action(dat, len);
		}
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_RxMonitor
*函数功能：串口字符串接收结束判断，在定时器中调用
*参数列表：
*   ms
*       参数类型：unsigned char型数据
*       参数描述：定时器延时时长（单位：ms）
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void UART_RxMonitor(unsigned char ms)
{
	static unsigned char ms30 = 0, UART_BuffIndex_Backup;
	ms30 += ms;
	if(! UART_ResiveStringFlag)return ;
	if(UART_BuffIndex_Backup != UART_BuffIndex)
	{
		UART_BuffIndex_Backup = UART_BuffIndex;
		ms30 = 0;
	}
	if(ms30 > 30)
		{
			ms30 = 0;
			UART_ResiveStringEndFlag = 1;
			UART_ResiveStringFlag = 0;
		}
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：UART_Read
*函数功能：将暂存数组中的数据读取出来。
*参数列表：
*   *to
*       参数类型：unsigned char型指针
*       参数描述：存储接收到的字符的位置
*   len
*       参数类型：unsigned char型数据
*       参数描述：要读取的字符串的长度
*返回值：unsigned char型数据，字符串的实际长度
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char UART_Read(unsigned char *to, unsigned char len)
{
	unsigned char i;
	if(UART_BuffIndex < len)len = UART_BuffIndex;
	for(i = 0;i < len;i ++)
		{
			*to = UART_Buff[i];
			to ++;
		}
	UART_BuffIndex = 0;
	return len;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：interrupt_UART
*函数功能：串口中断函数
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void interrupt_UART() interrupt 4
{
	if(TI)
	{
		TI = 0;
		UART_SendFlag = 1;
	}
	if(RI)
	{
		RI = 0;
		UART_ResiveFlag = 1;
		UART_Buff[UART_BuffIndex] = SBUF;
		UART_ResiveStringFlag = 1;
		UART_BuffIndex ++;
	}
}
