# PCF8591 AD/DA 芯片模块
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
&emsp;&emsp;&emsp;admin@hxlxz.com <br/>
<a href="/PCF8591/Sample/" target="_blank">Sample程序</a>  <br/>
功能描述：PCF8591 AD/DA芯片简单控制 <br/>
备注：使用该模块，请在config.h中定义IIC_SDA_SET_PCF8591常量为PCF8591的IIC总线的SDA数据接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define IIC_SDA_SET_PCF8591 P0^0 <br/>
&emsp;&emsp;&emsp;&emsp;使用该模块，请在config.h中定义IIC_SDA_SET_PCF8591常量为PCF8591的IIC总线的SCL数据接口。 <br/>
&emsp;&emsp;&emsp;&emsp;如 #define IIC_SCL_SET_PCF8591 P0^1 <br/>
本模块没有提供差分AD模块，如果有需要，欢迎提交issus。 <br/>

## unsigned char PCF8591_Read(unsigned char chanl);
函数名：PCF8591_Read <br/>
函数功能：读取AD转换得到的值（普通转换，非差分） <br/>
参数列表： <br/>
&emsp;channel <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：通道号 <br/>
返回值：一个unxigned char型数据，AD值 <br/>

## void PCF8591_DA(unsigned char dat);
函数名：PCF8591_DA <br/>
函数功能：启动PCF8591的DA输出 <br/>
参数列表： <br/>
&emsp;dat <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要输出的DA值 <br/>
