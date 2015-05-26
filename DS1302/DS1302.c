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
	功能描述：DS1302时钟芯片的时间设置及读取
            尽量使用封装好的函数进行操作，而不要使用直接对DS18B20读写的函数。
            使用该模块，请在config.h中定义DS1302_CE_SET常量为DS1302数据总线使能信号线。
                如 #define DS1302_CE_SET P0^0
            使用该模块，请在config.h中定义DS1302_IO_SET常量为DS1302数据总线数据传输线。
                如 #define DS1302_IO_SET P0^1
            使用该模块，请在config.h中定义DS1302_CK_SET常量为DS1302数据总线时钟信号线。
                如 #define DS1302_CK_SET P0^2
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg51.h>
#include<DS1302.h>

sbit DS1302_CE = DS1302_CE_SET;
sbit DS1302_IO = DS1302_IO_SET;
sbit DS1302_CK = DS1302_CK_SET;
//定义DS1302的数据总线接口

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：Delay1ms
*函数功能：延时1ms
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_ByteWrite
*函数功能：向DS1302写一个unsigned char型的数据或命令
*参数列表：
*   dat
*       参数类型：unsigned char型整数
*       参数描述：要写入的数据或命令
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_ByteWrite(unsigned char dat)
{
	unsigned char mask;
	for(mask = 0x01; mask != 0; mask <<= 1)
		{
			if(mask & dat)DS1302_IO = 1;
			else DS1302_IO = 0;
			DS1302_CK = 1;
			DS1302_CK = 0;
		}
	DS1302_IO = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_ByteRead
*函数功能：从DS1302读取一个unsigned char型的数据
*参数列表：
*   无
*返回值：一个unsigned char型变量：读取到的数据
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS1302_ByteRead()
{
	unsigned char mask, dat = 0;
	DS1302_IO = 1;
	for(mask = 0x01; mask != 0; mask <<= 1)
		{
			if(DS1302_IO)
                dat |= mask;
			DS1302_CK = 1;
			DS1302_CK = 0;
		}
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_SingleRead
*函数功能：向DS1302发送读取数据命令，并读一个unsigned char型的数据
*参数列表：
*   ddr
*       参数类型：unsigned char型整数
*       参数描述：寄存器地址，详见数据手册
*返回值：一个unsigned char型变量：读取到的数据
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS1302_SingleRead(unsigned char addr)
{
	unsigned char dat;
	EA = 0;
	DS1302_CE = 1;
	DS1302_ByteWrite(0x81 | (addr << 1));
	dat = DS1302_ByteRead();
	DS1302_CE = 0;
	EA = 1;
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_SingleWrite
*函数功能：向DS1302发送写数据命令，并写一个unsigned char型的数据
*参数列表：
*   dat
*       参数类型：unsigned char型整数
*       参数描述：要写入的数据
*   addr
*       参数类型：unsigned char型整数
*       参数描述：寄存器地址，详见数据手册
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_SingleWrite(unsigned char addr, unsigned char dat)
{
	EA = 0;
	DS1302_CE = 1;
	DS1302_ByteWrite(0x80 | (addr << 1));
	DS1302_ByteWrite(dat);
	DS1302_CE = 0;
	EA = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Write
*函数功能：DS1302Brust模式写入
*参数列表：
*   time
*       参数类型：struct DS1302_Time（参见DS1302.h）
*       参数描述：要写入的时间
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Write(struct DS1302_Time time)
{
	unsigned char i, dat[8] = {0x00};
	dat[0] = time.sec % 10 + time.sec / 10 * 16;
	dat[1] = time.min % 10 + time.min / 10 * 16;
	dat[2] = (time.hour % 10 + time.hour / 10 * 16) | 0x80;
	dat[3] = time.day % 10 + time.day / 10 * 16;
	dat[4] = time.month % 10 + time.month / 10 * 16;
	dat[5] = time.week % 10 + time.week / 10 * 16;
	dat[6] = time.year % 10 + time.year / 10 * 16;
	EA = 0;
	DS1302_CE = 1;
	DS1302_SingleWrite(7, 0x00);
	DS1302_ByteWrite(0xBE);
	for(i = 0; i < 8; i ++)
		DS1302_ByteWrite(dat[i]);
	DS1302_CE = 0;
	EA = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Read
*函数功能：DS1302Brust模式读取
*参数列表：
*   time
*       参数类型：struct DS1302_Time 型指针（参见DS1302.h）
*       参数描述：读取到的时间存放的位置。
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Read(struct DS1302_Time *time)
{
	unsigned char i, dat[8] = {0};
	EA = 0;
	DS1302_CE = 1;
	DS1302_ByteWrite(0xBF);
	for(i = 0; i < 8; i ++)
		{
			dat[i] = DS1302_ByteRead();
			EA = 1;
			Delay1ms();
			EA = 0;
		}
	DS1302_IO = 0;
	DS1302_CE = 0;
	EA = 1;
	*time.sec = dat[0] %16 + dat[0] / 16 * 10;
	*time.min = dat[1] %16 + dat[1] / 16 * 10;
	*time.hour = (dat[2] %16 + dat[2] / 16 * 10) & 0x7F;
	*time.day = dat[3] %16 + dat[3] / 16 * 10;
	*time.month = dat[4] %16 + dat[4] / 16 * 10;
	*time.week = dat[5] %16 + dat[5] / 16 * 10;
	*time.year = dat[6] %16 + dat[6] / 16 * 10;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Init
*函数功能：DS1302初始化
*参数列表：
*   无
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月9日
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_CK = 0;
	DS1302_IO = 1;
	DS1302_SingleWrite(7, 0x00);
}
