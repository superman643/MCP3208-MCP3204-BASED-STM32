#include "mcp.h"
#include "delay.h"

void MCP_PORTInit()
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = MCP_CS|MCP_CLK|MCP_DOUT;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化
 GPIO_SetBits(MCP_PORT,MCP_CS|MCP_CLK|MCP_DOUT);	 //output high

 GPIO_InitStructure.GPIO_Pin = MCP_DIN;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //float input
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(MCP_PORT, &GPIO_InitStructure);					 //根据设定参数初始化
}

float MCP3208_getAD(u8 channel)
{
	u8 i=0;
	u16 resualt=0;

	CS_Low;//CS=0
	CLK_Low;//CLK=0
	delay_us(3);

	for(i=0;i<6;i++)
	{
		CLK_High;//CLK=1
		delay_us(3);
		CLK_Low;//CLK=0
		if(channel&0x80) 
			DIN_High;
		else 
			DIN_Low;
		delay_us(3);
		channel<<=1;
	}

	CLK_High;//CLK=1
	delay_us(3);
	CLK_Low;//CLK=0
	delay_us(3);
	CLK_High;//CLK=1
	delay_us(3);
	CLK_Low;//CLK=0
	delay_us(3);

	for(i=0;i<12;i++)
	{
		resualt<<=1;
		CLK_High;//CLK=1
		if(Read_DOUT)
		resualt|=0x0001;
		delay_us(3);
		CLK_Low;//CLK=0
		delay_us(3);
	}
	CS_High;//CS=1

	return (resualt/4096.0)*Vref;
}

