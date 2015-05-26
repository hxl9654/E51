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
	2014年12月9日
	功能描述：DS1302时钟芯片的时间设置及读取
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_DS1302_
#define _HEAD_DS1302_

#include<intrins.h>
#include<config.h>
struct DS1302_Time{         //定义时间结构体
    unsigned char year;     //时间年（请使用十进制表示）
    unsigned char month;    //时间月（请使用十进制表示）
    unsigned char day;      //时间日（请使用十进制表示）
    unsigned char week;     //星期  （请使用十进制表示）
	unsigned char hour;     //时间时（请使用十进制表示）
	unsigned char min;      //时间分（请使用十进制表示）
	unsigned char sec;      //时间秒（请使用十进制表示）
};

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_SingleRead
*函数功能：向DS1302发送读取数据命令，并读一个unsigned char型的数据
*参数列表：
*   ddr
*       参数类型：unsigned char型整数
*       参数描述：寄存器地址，详见数据手册
*返回值：一个unsigned char型变量：读取到的数据
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS1302_SingleRead(unsigned char addr);
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
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_SingleWrite(unsigned char addr, unsigned char dat);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Write
*函数功能：DS1302Brust模式写入
*参数列表：
*   time
*       参数类型：struct DS1302_Time（参见DS1302.h）
*       参数描述：要写入的时间
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Write(struct DS1302_Time time);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Read
*函数功能：DS1302Brust模式读取
*参数列表：
*   time
*       参数类型：struct DS1302_Time 型指针（参见DS1302.h）
*       参数描述：读取到的时间存放的位置。
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Read(struct DS1302_Time *time);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS1302_Init
*函数功能：DS1302初始化
*////////////////////////////////////////////////////////////////////////////////////
void DS1302_Init();

#endif // _HEAD_DS1302_
