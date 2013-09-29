//----------------------------------------------------------------------------------------//
//							board.c								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	AVR board configuration definitions and routines						//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

//
//	Include headers
//
#include <avr/io.h>
#include "board.h"
#include "pwm.h"
#include "shell.h"

//
//	Main Initialization routine
//
void initBoard()
{
	#ifdef DEBUG
	avrPrintf("Init Board");
	#endif // DEBUG
	//
	//	Board I/O Pin Configurations
	//
	pinMode(PWM4_OUT_PIN, OUTPUT);
	pinMode(SOL_LED, OUTPUT);
	pinMode(EN_THERMAL_SENSORS, OUTPUT);
}

