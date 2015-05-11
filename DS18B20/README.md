# DS18B20温度传感器
文件名：18B20.h <br/>
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
	  admin@hxlxz.com <br/>
功能描述：DS18B20温度传感器的简单操作函数模块的头文件 <br/>
备注：尽量使用封装好的函数进行操作，而不要使用直接对DS18B20读写的函数。 <br/>
    使用该模块，请在程序中定义DS18B20_IO_SET常量为DS18B20的数据接口。 <br/>
    如 #define DS18B20_IO_SET P0^0 <br/>
    使用该模块，请在程序中定义STC_YX常量为STC单片机指令集名称。 <br/>
    如 #define STC_YX "STC_Y5" <br/>
    使用该模块，请在程序中定义XTAL常量为晶振频率 <br/>
    如 #define XTAL 11.059200 <br/>
## double DS18B20_GetTemp(unsigned char *addr);
函数名：DS18B20_GetTemp <br/>
函数功能：读取DS18B20，获得温度。 <br/>
参数列表： <br/>
   *addr <br/>
       参数类型：unsigned char型指针（连续8个unsigned char的数据） <br/>
       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00 <br/>
返回值：一个double型变量，获取到的温度值。（发生错误时，返回-999） <br/>
## bit DS18B20_Start(unsigned char *addr);
函数名：DS18B20_Start <br/>
函数功能：启动18B20温度转换。 <br/>
参数列表： <br/>
   *addr <br/>
       参数类型：unsigned char型指针（连续8个unsigned char的数据） <br/>
       参数描述：64字节的器件编号。特别的，Skip ROM时addr[0]请传入0x00 <br/>
返回值：一个bit型变量，启动是否正常（1；正常，0：失败） <br/>
## bit DS18B20_Init();
函数名：DS18B20_Init <br/>
函数功能：初始化18B20 <br/>
返回值：一个bit型变量，初始化是否正常（1；正常，0：失败） <br/>
## void DS18B20_Write(unsigned char dat);
函数名：DS18B20_Write  （尽量不要直接调用） <br/>
函数功能：向18B20写一个unsigned char型的数据或命令 <br/>
参数列表： <br/>
   dat <br/>
       参数类型：unsigned char型整数 <br/>
       参数描述：要写入的数据或命令 <br/>
## unsigned char DS18B20_Read();
函数名：DS18B20_Read   尽量不要直接调用） <br/>
函数功能：从DS18B20中读取一位数据 <br/>
返回值：一个unsigned char型变量，读取到的数据 <br/>

