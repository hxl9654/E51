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

	版权所有（C） <2015>   <何相龙>
	这一程序是自由软件，你可以遵照自由软件基金会出版的GNU通用公共许可证
	条款来修改和重新发布这一程序。你可以使用许可证的第三版，或者（根据你
	的选择）用任何更新的版本。

	发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定目的
	的隐含的担保。更详细的情况请参阅GNU通用公共许可证。

	你应该已经和程序一起收到一份GNU通用公共许可证的副本。如果还没有，请访
	问<http://www.gnu.org/licenses/>。

	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  568629794@qq.com
	2015年1月8日
	功能描述：74HC595的简单应用
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////外部声明//////////////////////////////////
extern void _74HC595_WriteData(uint8 dat);	//向74HC595写一个字节的数据（dat：数据）（所有数据发送完后，请调用_74HC595_Change();）。
extern void _74HC595_Change();				//向74HC595发送更新输出指令
////////////////////////////////////////////////////////////*/
#include<intrins.h>
#include<reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit SI=P1^0;	//数据输入接口
sbit SCK=P1^1;	//数据输入时钟信号
sbit RCK=P1^2;	//锁存器时钟信号

void _74HC595_Change()
{
	RCK=0;
	_nop_();_nop_();_nop_();_nop_();
	RCK=1;
	_nop_();_nop_();_nop_();_nop_();
	RCK=0;
}
void _74HC595_WriteData(uint8 dat)
{
	uint8 mask;
	RCK=0;
	for(mask=0x80;mask!=0;mask>>=1)
	{
		SCK=0;
		SI=dat&mask;
		SCK=1;
	}
	SCK=0;		
}