# SPI通信的IO口模拟实现(用于非STC15单片机）
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
&emsp;&emsp;&emsp;admin@hxlxz.com <br/>
<a href="/SPI_Analog/Sample/" target="_blank">Sample程序</a>  <br/>
功能描述：SPI通信的IO口模拟实现 <br/>
备注：如使用的单片机自带SPI通信相关硬件功能（如STC15W系列），推荐直接使用其硬件模块。 <br/>
&emsp;&emsp;&emsp;&emsp;注意：该模块仅能在较低速的SPI通信时使用，强烈建议使用STC15W4K系列带硬件SPI的单片机。 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_CPOL_SET常量为SPI通信的CPOL模式。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_CPOL_SET 1 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_CPOL_SET常量为SPI通信的CPHA模式。 <br/>
&emsp;&emsp;&emsp;&emsp;建议：如果要用SPI做多机通信，建议设置CPHA为1，这样可以提高本程序的稳定性。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_CPHA_SET 1 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_CS_SET常量为SPI总线的CS使能接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_CS_SET P0^0 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_SCLK_SET常量为SPI总线的SCLK时钟信号接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_SCLK_SET P0^1 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_MOSI_SET常量为SPI总线的MOSI信号接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_MOSI_SET P0^2 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义SPI_MISO_SET常量为SPI总线的MISO信号接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define SPI_MISO_SET P0^3 <br/>

## void SPI_Master_Init();
函数名：SPI_Master_Init <br/>
函数功能：SPI初始化（仅主模式使用） <br/>

## void SPI_Write(unsigned char dat);
函数名：SPI_Write <br/>
函数功能：SPI从模式：发送一位unsigned char 型的数据 <br/>
参数列表： <br/>
&emsp;dat <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要发送的数据 <br/>
       
## unsigned char SPI_Read();
函数名：SPI_Read <br/>
函数功能：SPI主模式：读取一位unsigned char 型的数据 <br/>
返回值：一个unsigned char型数据，读取到的数据。 <br/>

## void SPI_Slave_Send(unsigned char dat);
函数名：SPI_Slave_Send <br/>
函数功能：SPI从模式：回应一位unsigned char 型的数据 <br/>
参数列表： <br/>
&emsp;dat <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要回复的数据 <br/>

## unsigned char SPI_Slave_Resive();
函数名：SPI_Slave_Resive <br/>
函数功能：SPI从模式：接收一位unsigned char 型的数据 <br/>
返回值：一个unsigned char型数据，接收到的数据。 <br/>
