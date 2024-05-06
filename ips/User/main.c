#include "stm32f10x.h"
#include "OLED.h"
#include "rocker.h"
#include "Timer.h"
int main(void)
{
	uint8_t tmp = 0;
	OLED_Init();
	Rocker_Init();
	Timer_Init();
	OLED_Clear();
	while(1)
	{
		if(Flag_100ms == 1)
		{
			Flag_100ms = 0;
			tmp = Rocker_Scan();
		}
		OLED_ShowNum(1, 5,tmp, 1);		//显示转换结果第0个数据
		if(tmp == 9)OLED_ShowChar(2,2,'S');
	}
}
