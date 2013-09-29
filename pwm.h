//----------------------------------------------------------------------------------------//
//							pwm.h								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

#ifndef _PWM.CPP_h
#define _PWM.CPP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//	Module global variables
uint8_t pwm0_level;
uint8_t pwm1_level;
uint8_t pwm2_level;
uint8_t pwm3_level;
uint8_t pwm4_level;

//	Exported funcion prototypes
int myatoi(const char *string);
void vPwmInit(int argc, char *argv[]);
void vPwmStart(int argc, char *argv[]);
void vPwmStop(int argc, char *argv[]);
void vPwmSet(int argc, char *argv[]);

#endif

