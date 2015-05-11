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
	功能描述：EEPROM24C01芯片 EEPROM24C01的读写
	所需的文件支持：IIC.c
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////外部声明//////////////////////////////////
extern void EEPROM24C01_WriteString(uint8 addr,uint8 *dat,uint8 len);    //EEPROM24C01写入连续的数据（addr：地址，dat：数据，len：数据长度）
extern void EEPROM24C01_Write(uint8 addr,uint8 dat);   //EEPROM24C01写入一位数据（addr：地址，dat：数据）
extern void EEPROM24C01_ReadString(uint8 addr,uint8 len,uint8 *dat);    //EEPROM24C01读取连续的数据（addr：地址，dat：保存数据的数组，len：要读取的长度）
extern uint8 EEPROM24C01_Read(uint8 addr);  //EEPROM24C01读出一位数据（addr：地址），返回：读出的数据
////////////////////////////////////////////////////////////*/
#include<reg51.h>
#include<intrins.h>
typedef unsigned char uint8;
typedef unsigned int uint16;
extern void IIC_Start();
extern void IIC_Stop();
extern bit IIC_Write(uint8 dat);
extern uint8 IIC_Read(bit ACK);
uint8 EEPROM24C01_Read(uint8 addr)
{
	uint8 temp;
	IIC_Start();
	IIC_Write(0x50<<1);
	IIC_Write(addr);
	IIC_Start();
	IIC_Write((0x50<<1)|0x01);
	temp=IIC_Read(1);
	IIC_Stop();
	return temp;
}
void EEPROM24C01_ReadString(uint8 addr,uint8 len,uint8 *dat)
{
	IIC_Start();
	IIC_Write(0x50<<1);
	IIC_Write(addr);
	IIC_Start();
	IIC_Write((0x50<<1)|0x01);
	while(len>0)
	{
		*dat=IIC_Read(0);
		dat++;
		len--;
	}
	*dat=IIC_Read(1);
	IIC_Stop();
}
void EEPROM24C01_Write(uint8 addr,uint8 dat)
{
	bit temp;
	while(1)
	{
		IIC_Start();
		temp=IIC_Write(0x50<<1);
		if(temp)break;
		else IIC_Stop();
	}
	IIC_Write(addr);
	IIC_Write(dat);
	IIC_Stop();
}
void EEPROM24C01_WriteString(uint8 addr,uint8 *dat,uint8 len)
{
	bit temp;
	while(len>0)
	{
		while(1)
		{
			IIC_Start();
			temp=IIC_Write(0x50<<1);
			if(temp)break;
			else IIC_Stop();
		}
		IIC_Write(addr);
		while(len>0)
		{
			IIC_Write(*dat);
			len--;
			addr++;
			dat++;
			if((addr&0x07)==0)break;
		}
		IIC_Stop();
	}
}
