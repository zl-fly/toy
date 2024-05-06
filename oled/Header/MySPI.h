#ifndef _MYSPI_H_
#define _MYSPI_H_
#include "sys_function.h"
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
void MySPI_Send_8Byte(uint8_t data);

#endif