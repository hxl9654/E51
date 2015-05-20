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
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  568629794@qq.com
	2014年12月11日
	功能描述：PCF8591 AD/DA芯片简单控制
	备注：使用该模块，请在config.h中定义IIC_SDA_SET_PCF8591常量为PCF8591的IIC总线的SDA数据接口。
          如 #define IIC_SDA_SET_PCF8591 P0^0
          使用该模块，请在config.h中定义IIC_SDA_SET_PCF8591常量为PCF8591的IIC总线的SCL数据接口。
          如 #define IIC_SDA_SCL_PCF8591 P0^1
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg51.h>
#include<IIC_PCF8591.h>
bit PCF8591_DA_Flag = 0;	//DA功能是否打开标志位
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：Delay10ms
*函数功能：延时10毫秒
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2015年5月21日
*////////////////////////////////////////////////////////////////////////////////////
void Delay10ms()		//@33.1776MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 67;
	k = 183;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：PCF8591_Read
*函数功能：读取AD转换得到的值（普通转换，非差分）
*参数列表：
*   channel
*       参数类型：unsigned char型数据
*       参数描述：通道号
*返回值：一个unxigned char型数据，AD值
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char PCF8591_Read(unsigned char channel)
{
	unsigned char dat;
	IIC_Start_PCF8591();            	//向PCF8591的IIC总线发送通信起始信号
	IIC_Write_PCF8591(0x90);        	//向PCF8591的IIC总线发送一位数据：地址控制字（可能需要根据实际情况更改），并选择写操作
	if(PCF8591_DA_Flag)					//向PCF8591的IIC总线发送一位数据：要读取的频道（加入DA功能是否打开的判断，防止误操作）
		IIC_Write_PCF8591(channel + 0x40);	
	else IIC_Write_PCF8591(channel);		
	IIC_Stop_PCF8591();             	//向PCF8591的IIC总线发送通信结束信号
	
	Delay10ms();
	
	IIC_Start_PCF8591();            	//向PCF8591的IIC总线发送通信起始信号
	IIC_Write_PCF8591(0x91);        	//向PCF8591的IIC总线发送一位数据：地址控制字（可能需要根据实际情况更改），并选择读操作
	IIC_Read_PCF8591(0);
	dat = IIC_Read_PCF8591(1);      	//从PCF8591的IIC总线读取一位数据，并发送NAK
	IIC_Stop_PCF8591();             	//向PCF8591的IIC总线发送通信结束信号
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：PCF8591_DA
*函数功能：启动PCF8591的DA输出
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要输出的DA值
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*////////////////////////////////////////////////////////////////////////////////////
void PCF8591_DA(unsigned char dat)
{
	PCF8591_DA_Flag = 1;
	IIC_Start_PCF8591();        //向PCF8591的IIC总线发送通信起始信号
	IIC_Write_PCF8591(0x90);    //向PCF8591的IIC总线发送一位数据：地址控制字（可能需要根据实际情况更改），并选择写操作
	IIC_Write_PCF8591(0x40);    //向PCF8591的IIC总线发送一位数据：启动DA转换命令
	IIC_Write_PCF8591(dat);     //向PCF8591的IIC总线发送一位数据：要转换的参数值
	IIC_Stop_PCF8591();         //向PCF8591的IIC总线发送通信结束信号
}
