/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Micro, Platform=avr, Package=arduino
*/

#define __AVR_ATmega32U4__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

//
//
void CDC_Task();
void avrPrintf(const char * str);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\micro\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\Peltier_FW_Arduino.ino"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\adc.c"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\adc.h"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\board.c"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\board.h"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\pwm.c"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\pwm.h"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\shell.c"
#include "C:\Users\Ross\Documents\Arduino\Peltier_FW_Arduino\shell.h"
