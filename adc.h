//----------------------------------------------------------------------------------------//
//							pwm.h								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

#ifndef _ADC.CPP_h
#define _ADC.CPP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//	Exported Function Prototype
void ADCInit(int argc, char *argv[]);
void getADC_Result(int argc, char *argv[]);
int ADC_Channel_Read(uint8_t);

#endif

