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

	文件名：IIC_Analog.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：用单片机IO口模拟实现IIC通信
	备注：使用该模块，请在config.h中定义IIC_SDA_SET常量为IIC总线的SDA数据接口。
          如 #define IIC_SDA_SET P0^0
          使用该模块，请在config.h中定义IIC_SCL_SET常量为IIC总线的SCL数据接口。
          如 #define IIC_SCL_SET P0^1
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg51.h>
#include<IIC_Analog.h>

#define IICDelay() {nop_();nop_();nop_();nop_();}
//IIC通信中的简单延时

sbit IIC_SDA = IIC_SDA_SET;
sbit IIC_SCL = IIC_SCL_SET;

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Start
*函数功能：发送IIC总线起始信号
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*备注：由于函数相对简单易懂，不再提供详细注释
*////////////////////////////////////////////////////////////////////////////////////
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
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Stop
*函数功能：发送IIC总线停止信号
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*备注：由于函数相对简单易懂，不再提供详细注释
*////////////////////////////////////////////////////////////////////////////////////
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
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Write
*函数功能：向IIC总线发送一个unsigned char型数据
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要发送的数据
*返回值：一个bit型数，是否正常完成操作（1：正常，0：异常）
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
bit IIC_Write(unsigned char dat)
{
	unsigned char i, mask = 0x80;
	bit a;                              //用于存储接收到的ACK
	for(i = 0;i < 8;i ++)               //按位发送数据
		{
			if(dat&mask)IIC_SDA = 1;    //判断当前位是1还是0，对应拉高或拉低SDA
			else IIC_SDA = 0;
			IICDelay();                 //延时
			IIC_SCL = 1;                //拉高SCL
			mask >>= 1;                 //准备发送下一位数据
			IIC_SCL = 0;                //拉低SCL
		}
	IICDelay();                         //延时
	IIC_SDA = 1;                        //调整IIC总线
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	a=IIC_SDA;                          //读取ACK信号
	IIC_SCL = 0;
	return (~ a);                       //返回ACK信号（1：正常）
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：IIC_Read
*函数功能：从IIC总线读取一个unsigned char型数据
*参数列表：
*   ACK
*       参数类型：bit型数据
*       参数描述：数据读取结束后发送的应答位或非应答位
*返回值：一个unsigned char型变量，读取到的数据
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char IIC_Read(bit ACK)
{
	unsigned char i,mask = 0x80,dat = 0;
	IIC_SCL = 0;                            //准备IIC总线
	IIC_SDA = 1;
	for(i=0;i<8;i++)                        //按位读取数据
		{
			IICDelay();                     //延时
			IIC_SCL = 1;                    //拉高SCL
			IICDelay();                     //延时
			if(IIC_SDA)dat |= mask;         //读取1bit数据，并存在dat的相应文章
			mask >>= 1;
			IIC_SCL = 0;                    //拉低SCL，准备读取下一位数据
		}
	IICDelay();                             //延时
	IIC_SDA = ACK;                          //发送ACK或NAK信号
	IICDelay();                             //延时
	IIC_SCL = 1;                            //调整IIC总线
	IICDelay();
	IIC_SCL = 0;
	return dat;
}
