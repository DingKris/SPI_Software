#include "stm32f10x.h"                  // Device header
#include "sys.h"

#define Master_SPI_SCK		GPIO_Pin_1
#define Master_SPI_CS		GPIO_Pin_2
#define Master_SPI_MISO		GPIO_Pin_3
#define Master_SPI_MOSI		GPIO_Pin_4

#define SCK_HIGH()		GPIO_SetBits(GPIOA,Master_SPI_SCK)	//拉低时钟线
#define SCK_LOW()		GPIO_ResetBits(GPIOA,Master_SPI_SCK)	//拉高时钟线

#define CS_HIGH()		GPIO_SetBits(GPIOA,Master_SPI_CS)	//拉低时钟线
#define CS_LOW()		GPIO_ResetBits(GPIOA,Master_SPI_CS)	//拉高时钟线

#define MOSI PAout(3)
#define MISO PAin(4)


//CPHA=0;CPOL=0; 第一个边沿操作,上升沿操作，高位在前
u16 mySPI_Master_ReadWriteByte(u16 Data)	//主机写入数据
{
	int i;
	u16 ReceiveData=0x0000;
	CS_LOW();						//拉低片选线
	for(i=0;i<16;i++)				//16位数据循环
	{
		MOSI = ((Data<<i)&0x8000);	//写入数据
		SCK_HIGH();					//拉高时钟线
		if(MISO)
		ReceiveData|=(0x8000>>i); 	//读取数据
		SCK_LOW();					//拉低时钟线
	}
	CS_HIGH();						//拉高片选线
	return ReceiveData;				//返回接收的数据
}

