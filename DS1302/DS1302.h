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
void DS1302_Init(unsigned char *dat);  //DS1302初始化函数，在主函数开头调用，dat是设置的时间
unsigned char DS1302_SingleRead(unsigned char addr); //DS1302单字节读取，dat为读取数据存储位置，addr为寄存器地址，详见数据手册
void DS1302_SingleWrite(unsigned char addr,unsigned char dat);   //DS1302单字节写入，dat为写入数据，addr为寄存器地址，详见数据手册
void DS1302_BrustWrite(unsigned char *dat);  //DS1302Brust模式写入，dat为uint8型的拥有8个元素的数组
void DS1302_BrustRead(unsigned char *dat);   //DS1302Brust模式读取，dat为uint8型的拥有8个元素的数组

#endif // _HEAD_DS1302_
