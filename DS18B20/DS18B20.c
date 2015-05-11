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

	文件名：DS18B20.c
	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  admin@hxlxz.com
	功能描述：DS18B20温度传感器的简单操作函数模块
	备注：尽量使用封装好的函数进行操作，而不要使用直接对DS18B20读写的函数。
          使用该模块，请在程序中定义DS18B20_IO_SET常量为DS18B20的数据接口。
          如 #define DS18B20_IO_SET P0^0
          使用该模块，请在程序中定义STC_YX常量为STC单片机指令集名称。
          如 #define STC_YX "STC_Y5"
          使用该模块，请在程序中定义XTAL常量为晶振频率
          如 #define XTAL 11.059200
*////////////////////////////////////////////////////////////////////////////////////////
#define 6nop(); {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
//定义适用于STC_Y3,STC_Y5的nop延时
#ifndef DS18B20_IO_SET
#define DS18B20_IO_SET ;
#endif //如果没有定义DS18B20的IO口，则让编译器产生错误

#ifndef STC_YX
#define STC_YX "STC_Y5"
#endif //如果没有定义STC单片机的指令集，则默认为STC_Y5指令集

#ifndef XTAL
#define XTAL 11.059200
#endif //如果没有定义晶振频率，则默认为11.0592M晶振

sbit DS18B20_IO = DS18B20_IO_SET;
//定义DS18B20的数据IO口（请自行#define DS18B20_IO_SET P0^0 ）

/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DelayX10us
*函数功能：延时
*参数列表：
*   t
*       参数类型：unsigned char型整数
*       参数描述：要延时的时长，单位：10us
*返回值：无。
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*版本：1.1
*版本改动：重写函数，使之能在各种指令集、各晶振频率下工作
*作者：何相龙
*日期：2015年5月11日
*////////////////////////////////////////////////////////////////////////////////////
void DelayX10us(unsigned char t)
{
	unsigned char i;
	#if STC_YX == "STC_Y1"          //如果当前指令集为STC_Y1，由于该款单片机性能较差，所以用宏来针对不同的晶振频率选择延时函数
        #if XTAL < 8
        #elif XTAL >= 8 && XTAL < 9
            _nop_();
        #elif XTAL >= 9 && XTAL < 12
            i = 1;
            while(--i);
        #elif XTAL >= 12 && XTAL < 14
            i = 2;
            while(--i);
        #elif XTAL >= 14 && XTAL < 16
            i = 3;
            while(--i);
        #elif XTAL >= 16 && XTAL < 18
            i = 4;
            while(--i);
        #elif XTAL >= 18 && XTAL < 20
            i = 5;
            while(--i);
       #elif XTAL >= 20
            i = XTAL / 10 + 0.5;
            while(--i);
        #endif
    #else                           //如果当前指令集为STC_Y3或STC_Y5
        i = 2.2 * XTAL + 0.5;
        while (--i);
	#endif
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Init
*函数功能：初始化DS18B20
*参数列表：
*   无
*返回值：一个bit型变量，初始化是否正常（1；正常，0：失败）
*版本：1.0
*作者：何相龙
*日期：2015年5月11日
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Init()
{
	bit temp;
	EA=0;               //禁能中断，防止时序被干扰
	DS18B20_IO=0;       //拉低1-wine总线，发送Init信号
	DelayX10us(60);     //延时600us
	DS18B20_IO=1;       //释放总线
	DelayX10us(8);      //延时80us，等待器件响应
	temp=DS18B20_IO;    //读取总线
	while(!DS18B20_IO); //等待总线被释放
	EA=1;               //恢复中断使能
	return ~temp;       //返回获取到的初始化状态，为符合习惯，进行取反后再返回
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Write
*函数功能：向DS18B20写一个unsigned char型的数据或命令
*参数列表：
*   dat
*       参数类型：unsigned char型整数
*       参数描述：要写入的数据或命令
*返回值：无
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*////////////////////////////////////////////////////////////////////////////////////
void DS18B20_Write(unsigned char dat)
{
	unsigned char mask;
	EA=0;                               //禁能中断，防止时序被干扰
	for(mask=0x01;mask!=0;mask<<=1)     //按位发送数据
	{
		if(dat&mask)                    //获取当前位是否为1
		{
			DS18B20_IO=0;               //位开始信号
			#if STC_YX == "STC_Y1"      //稍微延时，防止错误
			_nop_();                    //对不同的单片机指令集做了不同的处理
			#else
            6nop();
			#endif
			DS18B20_IO=1;               //拉高总线，发送数据
			DelayX10us(8);              //延时80us
		}
		else                            //当前位为0
		{
			DS18B20_IO=0;               //拉低总线，发送数据
			DelayX10us(8);              //延时80us
			DS18B20_IO=1;               //释放总线
		}
			#if STC_YX == "STC_Y1"      //稍微延时，防止错误
			_nop_();_nop_();            //对不同的单片机指令集做了不同的处理
			#else
            6nop();6nop();
			#endif
	}
	EA=1;                               //恢复中断使能
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Read
*函数功能：从DS18B20中读取一位数据
*DS18B20
*   无
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS18B20_Read()
{
	unsigned char mask,dat=0;
	EA=0;                               //禁能中断，防止时序被干扰
	for(mask=0x01;mask!=0;mask<<=1)     //按位读取数据
	{
		DS18B20_IO=0;                   //拉低总线，发送起始信号
        #if STC_YX == "STC_Y1"          //稍微延时，防止错误
        _nop_();_nop_();                //对不同的单片机指令集做了不同的处理
        #else
        6nop();6nop();
        #endif

		DS18B20_IO=1;                   //释放总线
		DelayX10us(1);                  //延时10us
		if(DS18B20_IO)dat|=mask;        //读取总线，获取1位数据被保存
		DelayX10us(5);                  //延时50us，准备读取下一位数据
	}
	EA=1;                               //恢复中断使能
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_Start
*函数功能：启动DS18B20温度转换。
*参数列表：
*   *addr
*       参数类型：unsigned char型指针（连续8个unsigned char的数据）
*       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00
*返回值：一个bit型变量，启动是否正常（1；正常，0：失败）
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Start(unsigned char *addr)
{
	if(!DS18B20_Init())return 0;            //发送初始化信号，如果初始化错误，返回0
	if(addr[0]==0x00)DS18B20_Write(0xCC);   //如果addr[0]为0x00，发送Skip ROM指令
	else                                    //否则，发送Match ROM指令，并发送器件ROM号
	{
		DS18B20_Write(0x55);
		DS18B20_Write(addr[0]);
		DS18B20_Write(addr[1]);
		DS18B20_Write(addr[2]);
		DS18B20_Write(addr[3]);
		DS18B20_Write(addr[4]);
		DS18B20_Write(addr[5]);
		DS18B20_Write(addr[6]);
		DS18B20_Write(addr[7]);
	}
	DS18B20_Write(0x44);                    //发送启动温度转换指令
}
/*///////////////////////////////////////////////////////////////////////////////////
*函数名：DS18B20_GetTemp
*函数功能：读取DS18B20，获得温度。
*参数列表：
*   *addr
*       参数类型：unsigned char型指针（连续8个unsigned char的数据）
*       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00
*返回值：一个double型变量，获取到的温度值。（发生错误时，返回-999）
*版本：1.0
*作者：何相龙
*日期：2014年12月11日
*版本：1.1
*版本改动：修改返回值类型，直接返回double型数据
*作者：何相龙
*日期：2015年5月11日
*////////////////////////////////////////////////////////////////////////////////////
double DS18B20_GetTemp(unsigned char *addr)
{
	int temp;                                   //储存温度值技术中级数据
	unsigned char temp1,temp2;                  //储存温度值技术中级数据
	unsigned int temp3;                         //储存温度值技术中级数据
	double tempo;                               //储存最终得到的温度值
	bit flag = 0;                               //正负标记位
	if(!DS18B20_Init())return -999;             //发送初始化信号，如果初始化错误，返回-999
	if(addr[0] == 0x00)DS18B20_Write(0xCC);     //如果addr[0]为0x00，发送Skip ROM指令
	else                                        //否则，发送Match ROM指令，并发送器件ROM号
	{
		DS18B20_Write(0x55);
		DS18B20_Write(addr[0]);
		DS18B20_Write(addr[1]);
		DS18B20_Write(addr[2]);
		DS18B20_Write(addr[3]);
		DS18B20_Write(addr[4]);
		DS18B20_Write(addr[5]);
		DS18B20_Write(addr[6]);
		DS18B20_Write(addr[7]);
	}
	DS18B20_Write(0xBE);                        //发送读取温度指令
	temp1=DS18B20_Read();                       //读第一个unsigned char型数据，并暂存
	temp2=DS18B20_Read();                       //读第二个unsigned char型数据，并暂存
	temp3=(unsigned int)temp2;                  //将两位unsigned char型数据放到一个unsigned int型变量中
	temp3 <<= 8;
	temp3|=(unsigned int)temp1;
	DelayX10us(15);                             //延时150us
	if(temp3&0x8000)                            //如果得到的温度值是负值
	{
		temp3 &= 0x07FF;                        //获取温度值的绝对值
		temp = -temp3;
		flag = 1;                               //设置负值标志
	}
	else
	{
		temp3 &= 0x07FF;                        //获取温度值的绝对值
		temp = temp3;
	}
	tempo = temp >> 4;                          //处理温度值，存储到double型变量tempo中
	tempo += temp & 0x08 * 0.5 + temp & 0x04 * 0.25 + temp & 0x02 * 0.125 + temp & 0x01 * 0.6275;
	return tempo;
}
