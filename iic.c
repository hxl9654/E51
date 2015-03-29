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

	版权所有（C） <2014>   <何相龙>
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
	2014年12月9日
	功能描述：IO口模拟IIC通信
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////外部声明//////////////////////////////////
extern void IIC_Start();    //发出IIC通信起始信号
extern void IIC_Stop();     //发出IIC通信终止信号
extern bit IIC_Write(uint8 dat);    //IIC通信写入一个uint8型的数据（dat：要写入的数据）返回：1，成功；0，失败
extern uint8 IIC_Read(bit ACK);     //IIC通信读出一个uint8型的数据（ACK：0，非末位数据；1：末位数据），返回读出的数据
////////////////////////////////////////////////////////////*/
#include<reg51.h>
#include<intrins.h>
#define IICDelay() {nop_();nop_();nop_();nop_();}
sbit IIC_SDA=P3^6;
sbit IIC_SCL=P3^7;
typedef unsigned char uint8;

void IIC_Start()
{
	IIC_SCL=0;
	IICDelay();
	IIC_SDA=1;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SDA=0;
	IICDelay();
	IIC_SCL=0;
}
void IIC_Stop()
{
	IIC_SCL=0;
	IICDelay();
	IIC_SDA=0;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SDA=1;
}
bit IIC_Write(uint8 dat)
{
	uint8 i,mask=0x80;
	bit a;
	for(i=0;i<8;i++)
		{
			if(dat&mask)IIC_SDA=1;
			else IIC_SDA=0;
			IICDelay();
			IIC_SCL=1;
			mask>>=1;
			IIC_SCL=0;
		}
	IICDelay();
	IIC_SDA=1;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	a=IIC_SDA;
	IIC_SCL=0;
	return (~a); //返回1：正常
}
uint8 IIC_Read(bit ACK)
{
	uint8 i,mask=0x80,dat=0;
	IIC_SCL=0;
	IIC_SDA=1;
	for(i=0;i<8;i++)
		{
			IICDelay();
			IIC_SCL=1;
			IICDelay();
			if(IIC_SDA)dat|=mask;
			mask>>=1;
			IIC_SCL=0;
		}
	IICDelay();
	IIC_SDA=ACK;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SCL=0;
	return dat;
}
