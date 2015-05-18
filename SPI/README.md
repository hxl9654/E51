# SPI通信模块(STC15专用）
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
&emsp;&emsp;&emsp;admin@hxlxz.com <br/>
<a href="/SPI/Sample/" target="_blank">Sample程序</a>  <br/>
功能描述：SPI通信模块 <br/>
备注：仅适用于带有SPI功能的STC15系列单片机 <br/>

## void SPI_Read();
函数名：SPI_Read <br/>
函数功能：SPI主机模式：读取一位unsigned char型数据 <br/>
备注：读取到数据后，会调用用户自行编写的DataResive函数。从机模式下，此函数不可用——从机收到数据会自动调用DataResive函数。 <br/>

## void SPI_Send(unsigned char dat);
函数名：SPI_Send <br/>
函数功能：SPI发送一位unsigned char 型的数据 <br/>
参数列表： <br/>
&emsp;dat <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/> 
&emsp;&emsp;参数描述：要发送的数据 <br/>
返回值：一个double型变量，获取到的温度值。（发生错误时，返回-999） <br/>

## void SPI_Init(bit cpha, bit cpol, bit mode);
函数名：SPI_Init <br/> 
函数功能：SPI中断函数 <br/> 
参数列表： <br/> 
&emsp;cpha <br/> 
&emsp;&emsp;参数类型：bit型数据 <br/> 
&emsp;&emsp;参数描述：SPI CPHA参数值 <br/> 
&emsp;cpol <br/> 
&emsp;&emsp;参数类型：bit型数据 <br/> 
&emsp;&emsp;参数描述：SPI CPOL参数值 <br/> 
&emsp;mode <br/> 
&emsp;&emsp;参数类型：bit型数据 <br/> 
&emsp;&emsp;参数描述：SPI 主从模式设置（1：主模式，0：从模式） <br/> 

## void SPI_Close();
函数名：SPI_Close <br/> 
函数功能：关闭SPI <br/> 
