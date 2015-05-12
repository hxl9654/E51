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

	文件名：IIC.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：用单片机IO口模拟实现IIC通信
	备注：
*////////////////////////////////////////////////////////////////////////////////////////

	//2014年12月9日

#include<IIC.h>
#include<intrins.h>
#define IICDelay() {nop_();nop_();nop_();nop_();}
sbit IIC_SDA = P3^6;
sbit IIC_SCL = P3^7;

void IIC_Start()
{
	IIC_SCL = 0;
	IICDelay();
	IIC_SDA = 1;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	IIC_SDA = 0;
	IICDelay();
	IIC_SCL = 0;
}
void IIC_Stop()
{
	IIC_SCL = 0;
	IICDelay();
	IIC_SDA = 0;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	IIC_SDA = 1;
}
bit IIC_Write(unsigned char dat)
{
	unsigned char i, mask = 0x80;
	bit a;
	for(i = 0;i < 8;i ++)
		{
			if(dat&mask)IIC_SDA = 1;
			else IIC_SDA = 0;
			IICDelay();
			IIC_SCL = 1;
			mask >>= 1;
			IIC_SCL = 0;
		}
	IICDelay();
	IIC_SDA = 1;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	a=IIC_SDA;
	IIC_SCL = 0;
	return (~ a); //返回1：正常
}
unsigned char IIC_Read(bit ACK)
{
	unsigned char i,mask = 0x80,dat = 0;
	IIC_SCL = 0;
	IIC_SDA = 1;
	for(i=0;i<8;i++)
		{
			IICDelay();
			IIC_SCL = 1;
			IICDelay();
			if(IIC_SDA)dat |= mask;
			mask >>= 1;
			IIC_SCL = 0;
		}
	IICDelay();
	IIC_SDA = ACK;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	IIC_SCL = 0;
	return dat;
}
