/*
 * task-servomotor_lpc1769.c
 *
 *  Created on: 2 dic. 2020
 *      Author: ealegremendoza
 */
#include "servomotor_lpc1769.h"

/*
 *	@brief:		Initialization of the servomotor using the chip library.
 *	@param:		Nothing.
 *	@return:	Nothing.
 */
void Servo_Init(void)
{
	/* Set the pin to work as PWM. */
	PWM1_SelectChannel(LPC_PWM1,SERVO_PWM_CH);

	/* PREESCALE COUNTER register value. */
	PWM1_ValuePrescale(LPC_PWM1,PWMPRESCALE);

	/* MATCH register value. */
	PWM1_SetMatch(LPC_PWM1,MATCH0,PWMCycle);/* set PWM cycle(Ton+Toff)=100) */
	PWM1_SetMatch(LPC_PWM1,MATCH1,DutyCycle);/* Set 50% Duty Cycle for CH1 */

	/*Configure the action of TC == MR*/
	PWM1_ConfigMatch(LPC_PWM1, MATCH0,PWM_INTERR,PWM_RESET,PWM_STOP);

	/* Enable the new match value that we previously set */
	PWM1_EnableMatchValue(LPC_PWM1,MATCH0);
	PWM1_EnableMatchValue(LPC_PWM1,MATCH1);

	/* Sets control on edges and pwm outputs. */
	PWM1_ControlChannel(LPC_PWM1,CH1,PWM_EDGE_MODE,PWM_ENABLE);

	/* Restarts TC and PC for counting, does it in the next clock
	 * cycle after invoking the call.*/
	PWM1_ResetCounters(LPC_PWM1);

	/*Enable TC and PC for counting. In turn activates the PWM mode. */
	PWM1_EnableCounters(LPC_PWM1);

	Servo_Move(120); // Close gate.
}

/*
 * @brief:		Moves the servomotors uiDeg degrees.
 * @param:		uiDeg:	degrees.
 * @return:		0:error, 1:succes.
 */
uint8_t Servo_Move(uint32_t uiDeg )
{
	uint32_t uiPos;
	uiDeg%=180;
	uiPos = uiDeg*11+DutyMIN;

	if(uiPos <= DutyMAX)
	{
		PWM1_SetMatch(LPC_PWM1,MATCH1,uiPos);
		PWM1_EnableMatchValue(LPC_PWM1,MATCH1);
		return 1;	//exito
	}
	return 0; //error
}


#ifdef DEBUG_H_
/*
 *	@brief:		Initialization of the servomotor using registers.
 *	@param:		Nothing.
 *	@return:	Nothing.
 */
void Servo_Ini2(void)
{
	/*Configura el pin para que trabaje como PWM. */
	PWM1_SelectChannel(LPC_PWM1,SERVO_PWM_CH);
	LPC_PWM1->PR = PWMPRESCALE; //1 micro-second resolution
	LPC_PWM1->MR0 = PWMCycle; //20000us = 20ms period duration
	LPC_PWM1->MR1 = DutyCycle; //1ms - default pulse duration i.e. width
	LPC_PWM1->MCR = (1<<1); //Reset PWM TC on PWM1MR0 match
	LPC_PWM1->LER = (1<<1) | (1<<0); //update values in MR0 and MR1
	LPC_PWM1->PCR = (1<<9); //enable PWM output
	LPC_PWM1->TCR = (1<<1); //Reset PWM TC & PR
	LPC_PWM1->TCR = (1<<0) | (1<<3); //enable counters and PWM Mode
}

/*
 * @brief:		Verify that only numbers are sent to the servo
 * @param:		*str: string to send to servo
 * @return:		0- succes, 1- error.
 */
uint8_t checkServoData(const char *str)
{ // Revisa que solo se ingresen números enteros positivos.
  int i;
  int err=0;
  for(i=0;i<mystrlen(str);i++)
  {
    if(str[i]<'0' || str[i]>'9')
      err=1; //printf("< checkServoData error!");
  }
  return err;
}

#endif


