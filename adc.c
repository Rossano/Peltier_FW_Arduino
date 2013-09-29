//----------------------------------------------------------------------------------------//
//							pwm.c								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	AVR function handler for the ADC inputs.Those function are based on the 		//
//	Arduino analogWrite library functions.								//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

//	My include headers

//#include <avr/io.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include <stdint-gcc.h>
#include "Arduino.h"
#include "wiring_private.h"
//#include "WString.h"
//#include <WString.h>
#include "adc.h"
#include "board.h"
#include "shell.h"

//#define ADC_SETTINGS		ADC_REFERENCE_INT2560MV | ADC_RIGHT_ADJUSTED//ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED//ADC_REFERENCE_AREF | ADC_RIGHT_ADJUSTED
//#define EN_THERMAL_SENSORS	IOPORT_CREATE_PIN(PORTF,1)

//typedef unsigned char uint8_t;
//typedef unsigned int uint16_t;

/// <summary>
/// ADC Initialization function
/// This functions performs the basic configuration for the ADC.
/// It sets the reference for the ADC conversion, it enables the Thermal sensors and send back "OK"
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void ADCInit(int argc, char *argv[])
{
	#ifdef DEBUG
	avrPrintf("Entering ADCInit...\r\n");	
	#endif
	if (argc > 0)
	{
		//	If any parameter is passed to this function plot an error message and how to use the function
		vUsage("adc_init");
	}
	else
	{
		//	Set the analog reference for the ADC conversion
		analogReference(DEFAULT);
		//	Enable the Thermal Sensors
		digitalWrite(EN_THERMAL_SENSORS, HIGH);
		//	Display OK to the terminal
		avrPrintf("OK\r\n");
	}
}

/// <summary>
/// ADC Initialization function
/// It returns the level of the input after clipping.
/// </summary>
/// <param name="ch">ADC Channel to read.</param>
uint16_t readADC(uint8_t ch)
{
	uint16_t res;
	#ifdef DEBUG
	avrPrintf("Entering readADC...\r\n");
	#endif // DEBUG
	//
	//	This function goes into a big channel selector to launch the proper ADC channel reading function:
	//	If channel is 0-5 (valid ADC channels for Arduino Micro) launch the library function analogRead.
	//	If channel is the on Internal BandGap, or ADC ground or internal temperature sensor, recreate the
	//	code for reading from ADC
	//
	switch(ch)
	{
		//	Valid Arduino Micro ADC channels
		case 1: res = analogRead(A1); break;
		case 2: res = analogRead(A2); break;
		case 3: res = analogRead(A3); break;
		case 4: res = analogRead(A4); break;
		case 5: res = analogRead(A5); break;
		//	Internal band-gap channel
		case ADC_BG_CHANNEL:
		{

			// res = ADC_Channel_Read(ADC_BG_CHANNEL);			
			
			#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
			// For mega boards
			//const long InternalReferenceVoltage = 1115L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc reference
			// MUX4 MUX3 MUX2 MUX1 MUX0  --> 11110 1.1V (VBG)         -Selects channel 30, bandgap voltage, to measure
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR)| (0<<MUX5) | (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);				
			#else
			// For 168/328 boards
			//const long InternalReferenceVoltage = 1056L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc external reference
			// MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)         -Selects channel 14, bandgap voltage, to measure
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | channel; //((channel&MUX3)<<MUX3) | ((channel&MUX2)<<MUX2) | (channel&MUX1)<<MUX1) | ((channel&MUX0)<<MUX0);				
			#endif
			delay(50);  // Let mux settle a little to get a more stable A/D conversion
			// Start a conversion
			ADCSRA |= _BV( ADSC );
			// Wait for it to complete
			while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
			res = ADC;
			
			avrPrintf("OK\r\n");
			break;
		}	
		//	Internal ADC ground channel
		case ADC_GND_CHANNEL:
		{
			res = ADC_Channel_Read(ADC_GND_CHANNEL);
			
			#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
			// For mega boards
			//const long InternalReferenceVoltage = 1115L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc reference
			// MUX4 MUX3 MUX2 MUX1 MUX0  --> 11111 1.1V (GND)         -Selects channel 31, ground, to measure
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR)| (0<<MUX5) | (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
			#else
			// For 168/328 boards
			//const long InternalReferenceVoltage = 1056L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc external reference
			// MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)         -Selects channel 14, bandgap voltage, to measure
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | channel; //((channel&MUX3)<<MUX3) | ((channel&MUX2)<<MUX2) | (channel&MUX1)<<MUX1) | ((channel&MUX0)<<MUX0);
			#endif
			delay(50);  // Let mux settle a little to get a more stable A/D conversion
			// Start a conversion
			ADCSRA |= _BV( ADSC );
			// Wait for it to complete
			while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
			res = ADC;
			avrPrintf("OK\r\n");
			break;
		}			
		//	Internal Temperature Sensor channel		
		case ADC_TEMPERATURE_SENSOR:
		{			
			//res = ADC_Channel_Read(ADC_TEMPERATURE_SENSOR);
			
			#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
			// For mega boards
			//const long InternalReferenceVoltage = 1115L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc reference
			// MUX4 MUX3 MUX2 MUX1 MUX0  --> 11110 1.1V (VBG)         -Selects channel 30, bandgap voltage, to measure
			ADCSRB |= (1<<MUX5);
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR)| (0<<MUX4) | (0<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);
			#else
			// For 168/328 boards
			//const long InternalReferenceVoltage = 1056L;  // Adjust this value to your boards specific internal BG voltage x1000
			// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc external reference
			// MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)         -Selects channel 14, bandgap voltage, to measure
			ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | channel; //((channel&MUX3)<<MUX3) | ((channel&MUX2)<<MUX2) | (channel&MUX1)<<MUX1) | ((channel&MUX0)<<MUX0);
			#endif
			delay(50);  // Let mux settle a little to get a more stable A/D conversion
			// Start a conversion
			ADCSRA |= _BV( ADSC );
			// Wait for it to complete
			while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
			res = ADC;
			
			avrPrintf("OK\r\n");
			break;
			//avrPrintf("OK\r\n");
			//break;
		}
		//	None of the above channels is found, returns an error message
		default: 
		{
			avrPrintf("Error: Channel not implemented\r\n");
			return 0;
		}			
	}
	//	Else return the conversion result on 16 bits
	return res;
}

/// <summary>
/// Get the conversion result from ADC 
/// This function converts the ADC channel to a numeric format and launch a conversion.
/// Then it converts back the result in ASCII and send it through the terminal ending sending "OK"
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void getADC_Result(int argc, char *argv[])
{
	if (argc < 1)
	{
		//	If there is not at least an argument function is wrongly used and the way of using it is displayed
		vUsage("adc_get <channel>");
	}
	else
	{
		//uint8_t channel = (uint8_t)(*argv[1]) - '0';
		//	Convert the first argument into a numeric format
		uint8_t channel = atoi(argv[0]);
		//	Perform a conversion on the resulting channel
		uint16_t res = readADC(channel);
		//ADC_Send_DataType.word = res;
		//	Converts back the result in ASCII and send it through the terminal
		char str[5];// = "\0\0\0\0\0";
		itoa(res, str, 10);
		//str[0] = ADC_Send_DataType.high;
		////str[1] = ADC_Send_DataType.low;
		//str = argv[0];
		//String str(argv[0]);
		
		//uint16_t res = readADC(str.toInt());
		//itoa(res, str, 10);
		avrPrintf("ADC-> ");
		avrPrintf(str);
		avrPrintf(CR);
		avrPrintf("OK\r\n");
	}
}

//
//	DO NOT USE THIS FUNCTION, it doesn't work
//
int ADC_Channel_Read(uint8_t channel)
{
	#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
	// For mega boards
	const long InternalReferenceVoltage = 1115L;  // Adjust this value to your boards specific internal BG voltage x1000
	// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc reference
	// MUX4 MUX3 MUX2 MUX1 MUX0  --> 11110 1.1V (VBG)         -Selects channel 30, bandgap voltage, to measure
	//ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR)| (0<<MUX5) | (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);
	ADMUX |= (0<<REFS1) | (1<<REFS0) | (0<<ADLAR)| ((channel & MUX4)<<MUX4) | ((channel & MUX3)<<MUX3) | ((channel & MUX2)<<MUX2) | ((channel & MUX1)<<MUX1) | ((channel & MUX0)<<MUX0);
					
	#else
	// For 168/328 boards
	const long InternalReferenceVoltage = 1056L;  // Adjust this value to your boards specific internal BG voltage x1000
	// REFS1 REFS0          --> 0 1, AVcc internal ref. -Selects AVcc external reference
	// MUX3 MUX2 MUX1 MUX0  --> 1110 1.1V (VBG)         -Selects channel 14, bandgap voltage, to measure
	ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | channel; //((channel&MUX3)<<MUX3) | ((channel&MUX2)<<MUX2) | (channel&MUX1)<<MUX1) | ((channel&MUX0)<<MUX0);
					
	#endif
	delay(50);  // Let mux settle a little to get a more stable A/D conversion
	// Start a conversion
	ADCSRA |= _BV( ADSC );
	// Wait for it to complete
	while( ( (ADCSRA & (1<<ADSC)) != 0 ) );
	return ADC;
}