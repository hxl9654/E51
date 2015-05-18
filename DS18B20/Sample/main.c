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
	功能描述：DS18B20温度传感器的简单操作函数模块的Sample程序
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg51.h>
#include<DS18B20.h>
unsigned char addr = 0x00;                          //Skip ROM
bit UART_SendFlag = 0;
void Delay1000ms();
void UART_Conf(unsigned int baud);
void UART_SendString(unsigned char *dat,unsigned char len);
int main()
{
	double temperature;                             //获取到的温度存储在这个变量
	int temp;                                       //中间临时变量
	char SendString[10]={0};                        //串口待发送字符串暂存
	UART_Conf(9600);                                //串口通信配置函数
	while(1)
	{
		if(! DS18B20_Start(&addr))                  //尝试初始化
		{
			UART_SendString("ERROR\n", 6);          //如果失败，串口发送ERROR
			Delay1000ms();                          //延时1秒
		}
		else
		{
			Delay1000ms();                          //延时1秒
			temperature = DS18B20_GetTemp(&addr);   //读取DS18B20，获取温度信息
			temp = (int) temperature;               //处理温度数据
			SendString[0] = temp / 100 + '0';
			SendString[1] = temp / 10 % 10 + '0';
			SendString[2] = temp % 10 + '0';
			SendString[3] = '.';
			temp = (temperature - temp) * 100;
			SendString[4] = temp / 10 + '0';
			SendString[5] = temp % 10 + '0';
			SendString[6] = '\n';
			UART_SendString(SendString, 7);         //通过串口发送温度数据
		}
	}
}
void interrupt_UART() interrupt 4                   //串口中断函数
{
	if(TI)
	{
		TI = 0;
		UART_SendFlag = 1;
	}
	if(RI)
	{
		RI = 0;
	}
}
void UART_Conf(unsigned int baud)                   //UART设置函数（buad：欲设置的波特率）
{
	TL1 = TH1 = 256 - 11059200 / 12 / 32 / baud;
	EA = 1;
	ES = 1;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TR1 = 1;
}
void UART_SendString(unsigned char *dat,unsigned char len)  //串口通信：发送一个字符串（dat：要发送的字符串，len：字符串长度）
{
	while(len)
	{
		len --;
		SBUF =* dat;
		dat ++;
		while(! UART_SendFlag);
		UART_SendFlag = 0;
	}
}
void Delay1000ms()		//软件延时函数
{
	unsigned char i, j, k;

	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
