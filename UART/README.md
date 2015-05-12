# 串口字符串通信模块
作者：何相龙 <br/>
邮箱：qwgg9654@gmail.com <br/>
&emsp;&emsp;&emsp;admin@hxlxz.com <br/>
<a href="/UART/Demo/" target="_blank">Demo程序</a>  <br/>
功能描述：串口字符串通信模块 <br/>
备注：使用该模块接收数据时，请在你的程序中定义编写UART_Action函数，详见下面的说明。  <br/>
&emsp;&emsp;使用该模块，请在config.h中定义BUFFMAX常量为数据缓存数组最大值。  <br/>
&emsp;&emsp;&emsp;&emsp;如 #define BUFFMAX 64  <br/>
&emsp;&emsp;使用该模块，请在config.h中定义XTAL常量为晶振频率（单位：兆赫兹）。  <br/>
&emsp;&emsp;&emsp;&emsp;如 #define XTAL 11.059200  <br/>
## extern void UART_Action(unsigned char *dat, unsigned char len);
<b>此函数须另行编写，当串口完成一个字符串结束后会自动调用。</b>  <br/>
其中，dat是接收到的字符串的首地址指针，len是接收到的字符串的长度。  <br/>
关于如何编写并使用这个函数，请参考Demo程序。  <br/>
## void UART_Conf(uint16 baud);
函数名：UART_Conf <br/>
函数功能：配置串口 <br/>
参数列表： <br/>
&emsp;baud <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要设置的波特率 <br/>
## void UART_SendString(uint8 *dat,uint8 len);
函数名：UART_SendString <br/>
函数功能：向串口发送一个字符串 <br/>
参数列表： <br/>
&emsp;*dat <br/>
&emsp;&emsp;参数类型：unsigned char型指针 <br/>
&emsp;&emsp;参数描述：要发送的字符串的首地址 <br/>
&emsp;len <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：要发送的字符串的长度 <br/>
## void UART_RxMonitor(uint8 ms);
函数名：UART_RxMonitor <br/>
函数功能：串口字符串接收结束判断，在定时器0中断函数中调用 <br/>
参数列表： <br/>
&emsp;ms <br/>
&emsp;&emsp;参数类型：unsigned char型数据 <br/>
&emsp;&emsp;参数描述：定时器延时时长（单位：ms） <br/>
## void UART_Driver();
函数名：UART_Driver <br/>
函数功能：串口通信监控函数，在主循环中调用。 <br/>
&emsp;&emsp;&emsp;&emsp;如果接收到字符串，会自动调用另行编写的UART_Action(unsigned char *dat,unsigned char len) <br/>