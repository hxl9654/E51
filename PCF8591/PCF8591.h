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
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_PCF8591_
#define _HEAD_PCF8591_

#include<intrins.h>
#include<config.h>
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：PCF8591_Read
*函数功能：读取AD转换得到的值（普通转换，非差分）
*参数列表：
*   chanl
*       参数类型：unsigned char型数据
*       参数描述：通道号
*返回值：一个unxigned char型数据，AD值
*////////////////////////////////////////////////////////////////////////////////////
unsigned char PCF8591_Read(unsigned char chanl);
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：PCF8591_DA
*函数功能：启动PCF8591的DA输出
*参数列表：
*   dat
*       参数类型：unsigned char型数据
*       参数描述：要输出的DA值
*////////////////////////////////////////////////////////////////////////////////////
void PCF8591_DA(unsigned char dat);

#endif
