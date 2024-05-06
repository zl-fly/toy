#include "MySPI.h"
/***************************************************************
  *  @brief		  	硬件SPI初始化
  *  @param[in]	  	none
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void MySPI_Init(void)
{
	//开启时钟 GPIOA和SPI1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	//配置管脚
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA4引脚初始化为推挽输出
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//硬件Spi初始化
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//时钟分频128分频
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						//spi相位，第一个边沿输出
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							//spi极性，低电平
	SPI_InitStructure.SPI_CRCPolynomial = 7;							//CRC多项式，暂时用不到，给默认值7
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//8位
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//方向，选择2线全双工
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					//高位先行
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//spi主模式
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							//软件控制Nss
	SPI_Init(SPI1, &SPI_InitStructure);									//将结构体变量交给SPI_Init，配置SPI1
	
	//Spi使能
	SPI_Cmd(SPI1,ENABLE);
}

/***************************************************************
  *  @brief		  	片选 
  *  @param[in]	  	value 写入的电平值
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void MySPI_W_CS(uint8_t value)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,value);
}

/***************************************************************
  *  @brief		  	SPI起始信号
  *  @param[in]	  	none
  *  @param[out]	none
  *  @note			拉低cs开始时序
 **************************************************************/
void MySPI_Start(void)
{
	MySPI_W_CS(0);
}

/***************************************************************
  *  @brief		  	SPI停止信号
  *  @param[in]	  	none
  *  @param[out]	none
  *  @note			拉高cs停止时序
 **************************************************************/
void MySPI_Stop(void)
{
	MySPI_W_CS(1);
}

/***************************************************************
  *  @brief		  	发送8位数据
  *  @param[in]	  	发送的数据 data
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void MySPI_Send_8Byte(uint8_t data)
{
	uint8_t time_out = 250;
	//等待发送数据寄存器空 超时控制
	while(time_out)
	{
		if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == SET)
		{
			time_out = 0;
		}
		else 
		{
			time_out--;
		}
	}	
	SPI_I2S_SendData(SPI1, data);								//写入数据到发送数据寄存器，开始产生时序
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);	//等待接收数据寄存器非空
	//return SPI_I2S_ReceiveData(SPI1);								//读取接收到的数据并返回
}
