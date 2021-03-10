/*
 * task-servomotor_lpc1769.h
 *
 *  Created on: 2 dic. 2020
 *      Author: ealegremendoza
 *  @note:
 *  	Working on Servo MG90
 *  @note:
 *  	Brown wire 	- GND
 *  	Red wire	- VCC 	(5~6.5V)
 *  	Yellow wire	- PWM SIGNAL
 *  @note:
 *  	Testing circuit if you haven't servo:
 *  	+5Vdc - LED_ANODE
 *  	LED_CATHODE - C_NPN_TBJ
 *  	PWM_SIGNAL_LPC - B_NPN_TBJ
 *  	E_NPN_TBJ - GND
 */

#ifndef SRC_TASKS_TASK_SERVOMOTOR_LPC1769_H_
#define SRC_TASKS_TASK_SERVOMOTOR_LPC1769_H_
#include "headers.h"
// SERVOMOTOR MG90S
#define SERVO_PWM_CH	CH1
#define PWMPRESCALE 	(25-1)
#define MATCH0			0
#define MATCH1			1
#define	PWMCycle		20000
#define DutyCycle		1250
#define DutyMIN			500
#define DutyMAX			2500

#define PWM_ENABLE		1
#define	SINGLE_EDGE		0
#define PWM_EDGE_MODE	SINGLE_EDGE
#define PWM_INTERR		0
#define	PWM_RESET		1
#define PWM_STOP		0

#define CLOSEGATE	0
#define OPENGATE	1

#define DISABLEFLG	0
#define ENABLEFLG	1

/*
 *	@brief:		Initialization of the servomotor using the chip library.
 *	@param:		Nothing.
 *	@return:	Nothing.
 */
void Servo_Init(void);

/*
 * @brief:		Moves the servomotors uiDeg degrees.
 * @param:		uiDeg:	0-180 degrees.
 * @return:		0:error, 1:succes.
 */
uint8_t Servo_Move(uint32_t uiDeg);



#ifdef DEBUG_H_

/*
 *	@brief:		Initialization of the servomotor using registers.
 *	@param:		Nothing.
 *	@return:	Nothing.
 */
void Servo_Ini2(void);


/*
 * @brief:		Verify that only numbers are sent to the servo
 * @param:		*str: string to send to servo
 * @return:		0- succes, 1- error.
 */
uint8_t checkServoData(const char *str);
#endif

#endif /* SRC_TASKS_TASK_SERVOMOTOR_LPC1769_H_ */
