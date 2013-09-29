//----------------------------------------------------------------------------------------//
//							board.h								//
//																//
//----------------------------------------------------------------------------------------//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

#ifndef _BOARD_h
#define _BOARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//
//	Configuration Defines
//
#define EN_THERMAL_SENSORS				A4 //IOPORT_CREATE_PIN(PORTF, 1)
#define PELTIER_THERMAL_SENSOR_ADC_CH	A2
#define BOARD_THERMAL_SENSOR_ADC_CH		A3
#define ADC_BG_CHANNEL					30
#define ADC_GND_CHANNEL					31
#define ADC_TEMPERATURE_SENSOR			39
#define PWM4_OUT_PIN					13
#define SOL_LED							13
#define PWM_PELTIER_PIN					10
#define PWM2_OUT_PIN					PWM_PELTIER_PIN

//
//	Defines which PWM channels are available
//
#define PWM0_AVAILABLE	true
#define PWM1_AVAILABLE	true
#define PWM2_AVAILABLE	true
#define PWM3_AVAILABLE	true
#define PWM4_AVAILABLE	true

//
//	Defines which ADC channels are available
//
#define ADC_CH0_AVAILABLE	true
#define ADC_CH1_AVAILABLE	true
#define ADC_CH2_AVAILABLE	false	
#define ADC_CH3_AVAILABLE	false
#define ADC_CH4_AVAILABLE	true
#define ADC_CH5_AVAILABLE	true
#define ADC_CH6_AVAILABLE	true
#define ADC_CH7_AVAILABLE	true
#define ADC_CH8_AVAILABLE	false
#define ADC_CH9_AVAILABLE	false
#define ADC_CH10_AVAILABLE	false
#define ADC_CH11_AVAILABLE	false
#define ADC_CH12_AVAILABLE	true
#define ADC_CH13_AVAILABLE	true

//	Function prototypes
void initBoard();

#endif

