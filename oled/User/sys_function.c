#include "sys_function.h"
/***************************************************************
  *  @brief		  	延时函数
  *  @param[in]	  	时间限制us
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/***************************************************************
  *  @brief		  	延时函数
  *  @param[in]	  	时间限制ms
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/***************************************************************
  *  @brief		  	延时函数
  *  @param[in]	  	时间限制s
  *  @param[out]	none
  *  @note			none
 **************************************************************/
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
