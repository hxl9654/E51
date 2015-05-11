#ifndef _HEAD_18B20_
#define _HEAD_18B20_

extern int DS18B20_GetTemp(uint8 *addr);    //读取18B20，获得温度。（addr：64字节的器件编号，skip ROM：addr[0]=0x00）返回温度值。
extern void DS18B20_Start(uint8 *addr);     //启动18B20温度转换。（addr：64字节的器件编号，skip ROM：addr[0]=0x00）。每次读出温度后必须重新启动温度转换。
extern bit DS18B20_Init();  //初始化18B20，也可用于检测器件是否存在。返回值1：正常；2：异常。

#endif // _HEAD_18B20_
