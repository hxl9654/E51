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

	文件名：IIC.h
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：用单片机IO口模拟实现IIC通信-头文件
	备注：
*////////////////////////////////////////////////////////////////////////////////////////

	//2014年12月9日

void IIC_Start();    //发出IIC通信起始信号
void IIC_Stop();     //发出IIC通信终止信号
bit IIC_Write(unsigned char dat);    //IIC通信写入一个uint8型的数据（dat：要写入的数据）返回：1，成功；0，失败
unsigned char IIC_Read(bit ACK);     //IIC通信读出一个uint8型的数据（ACK：0，非末位数据；1：末位数据），返回读出的数据

