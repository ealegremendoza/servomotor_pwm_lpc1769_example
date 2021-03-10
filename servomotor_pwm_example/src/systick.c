/*
 * systick.c
 *
 *  Created on: 9 mar. 2021
 *      Author: ealegremendoza
 */

#include "systick.h"
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */


void SysTick_Handler(void)
{
	static uint32_t Divisor_1sec=1000;
	static uint32_t Divisor_1min=60;
	static uint32_t servo_degrees = 0;
	Divisor_1sec--;

	if(0==Divisor_1sec)	//1 sec
	{
		Divisor_1sec=1000;
		Divisor_1min--;

		if(Servo_Move(servo_degrees))
		{
			DEBUGOUT("sm\n");
			servo_degrees+=45;
		}

		if(0==Divisor_1min)	//1 min
		{
			Divisor_1min=60;
		}
	}
}



void SysTick_Init(uint32_t freq)
{
	if(freq > 0xffffff)
		return;
	/* Enable and setup SysTick Timer at a periodic rate */
	/* Configuro el systick para que de ticks cada 1ms con TICKRATE_HZ1=1000*/
	//SysTick_Config(ticks*100);
	SysTick_Config(SystemCoreClock / freq);
}


