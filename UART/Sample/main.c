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

	文件名：main.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：串口字符串通信模块的Sample程序
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg52.h>
#include<UART.h>
#include<config.h>
unsigned char T0H, T0L;		//定时器参数存储变量
void Timer0_Init(unsigned char ms);
void UART_Action(unsigned char *dat, unsigned char len)
{
	unsigned char pdata msg[64] = "";		//收到的消息的暂存数组
	unsigned char i;
	for(i = 0;i < len;i ++)					//将收到的消息放到暂存数组
	{
		msg[i] = *dat;
		dat ++;
	}
	UART_SendString("I've received ", 14);	//发送"I've received "
	UART_SendString(msg, len);				//将收到的消息发送到串口
	UART_SendString("\n", 1);				//发送换行符
}

int main()
{
	UART_Conf(9600);		//配置串口波特率为9600
	Timer0_Init(1);			//配置定时器中断发生频率为1ms一次
	UART_SendString("This is a demo program.\n", 24);	//发送"This is a demo program.\n"
	while(1)
	{
		UART_Driver();		//监控串口
	}
}
void Timer0_Init(unsigned char ms)
{
	unsigned int temp;						//用于计算的中间变量
	temp = 65536 - ms * XTAL * 1000 / 12;	//计算定时器初值，并配置习惯寄存器
	T0H = (unsigned char)(temp >> 8);
	T0L = (unsigned char)(temp);
	TH0 = T0H;
	TL0 = T0L;
	TMOD &= 0XF0;							//配置定时器工作模式为模式1
	TMOD |= 0X01;
	ET0 = 1;								//使能定时器0中断
	TR0 = 1;								//使能定时器0
}
void Interrupt_Timer0() interrupt 1
{
	TH0 = T0H;				//定时器寄存器赋初值
	TL0 = T0L;
	UART_RxMonitor(1);		//串口通信监控
}
