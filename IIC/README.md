# 用单片机IO口模拟实现IIC通信
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
&emsp;&emsp;&emsp;admin@hxlxz.com <br/>
<a href="/IIC/Demo/" target="_blank">Demo程序</a>  <br/>
功能描述：用单片机IO口模拟实现IIC通信 <br/>
备注：使用该模块，请在config.h中定义IIC_SDA常量为IIC总线的SDA数据接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define IIC_SDA_SET P0^0 <br/>
&emsp;&emsp;&emsp;使用该模块，请在config.h中定义IIC_SCL常量为IIC总线的SCL数据接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define IIC_SCL_SET P0^1 <br/>
## void IIC_Start();
函数名：IIC_Start <br/>
函数功能：发送IIC总线起始信号 <br/>
## void IIC_Stop();
函数名：IIC_Stop <br/>
函数功能：发送IIC总线停止信号 <br/>
## bit IIC_Write(unsigned char dat);
函数名：IIC_Write <br/>
函数功能：向IIC总线发送一个unsigned char型数据 <br/>
参数列表： <br/>
&emsp;dat <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要发送的数据 <br/>
返回值：一个bit型数，是否正常完成操作（1：正常，0：异常） <br/>
## unsigned char IIC_Read(bit ACK);
函数名：IIC_Read <br/>
函数功能：从IIC总线读取一个unsigned char型数据 <br/>
参数列表： <br/>
&emsp;ACK <br/>
&emsp;&emsp;参数类型：bit型数据 <br/>
&emsp;&emsp;参数描述：数据读取结束后发送的应答位或非应答位 <br/>
返回值：一个unsigned char型变量，读取到的数据 <br/>
