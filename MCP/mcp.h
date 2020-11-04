#ifndef _MCP_H_
#define _MCP_H_

#include "sys.h"

#define MCP_PORT GPIOA
#define MCP_CS   GPIO_Pin_4
#define MCP_CLK  GPIO_Pin_5
#define MCP_DIN  GPIO_Pin_7
#define MCP_DOUT GPIO_Pin_6


#define CLK_High  GPIO_SetBits(MCP_PORT,MCP_CLK)
#define CLK_Low   GPIO_ResetBits(MCP_PORT,MCP_CLK)

#define CS_High   GPIO_SetBits(MCP_PORT,MCP_CS)
#define CS_Low    GPIO_ResetBits(MCP_PORT,MCP_CS)

#define DIN_High  GPIO_SetBits(MCP_PORT,MCP_DIN)
#define DIN_Low   GPIO_ResetBits(MCP_PORT,MCP_DIN)

#define Read_DOUT GPIO_ReadInputDataBit(MCP_PORT,MCP_DOUT)

#define MCP3208_CHO 0xC0
#define MCP3208_CH1 0xC8
#define MCP3208_CH2 0xD0
#define MCP3208_CH3 0xD8
#define MCP3208_CH4 0xE0
#define MCP3208_CH5 0xE8
#define MCP3208_CH6 0xF0
#define MCP3208_CH7 0xF8

#define Vref 3.22

float MCP3208_getAD(u8 channel);
void MCP_PORTInit(void);

#endif
