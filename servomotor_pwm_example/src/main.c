/*
===============================================================================
 Name        : main.c
 Author      : ealegremendoza
 Version     : 1
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "headers.h"

void SysInit(void);

int main(void)
{
	SysInit();
	DEBUGOUT("> main\n");
    while(1) {
    	// check systick handler
    }
    return 0 ;
}

void SysInit(void)
{
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();

	//	Initialize Systick with a frequency of 1000Hz (1ms)
	SysTick_Init(TICKRATE_HZ1);

	// PWM ch1 init
	Servo_Init();

}
