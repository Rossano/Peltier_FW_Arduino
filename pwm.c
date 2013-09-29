//----------------------------------------------------------------------------------------//
//							pwm.c								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	AVR function handler for the pwm outputs. Those function are based on the 	//
//	Arduino analogWrite library functions.								//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

//	My include headers
#include <stdint.h>
#include <avr/io.h>
#include "Arduino.h"
#include "board.h"
#include "pwm.h"
#include "shell.h"

//	Local Function prototypes
void Pwm0_Start();
void Pwm0_Stop();
void Pwm1_Start();
void Pwm1_Stop();
void Pwm2_Start();
void Pwm2_Stop();
void Pwm3_Start();
void Pwm3_Stop();
void Pwm4_Start();
void Pwm4_Stop();

/// <summary>
/// 10 bit clipping function
/// It returns the level of the input after clipping.
/// </summary>
/// <param name="level">Value to clip on 10 bits</param>
uint16_t clip10(uint16_t level)
{
	//	If the level value is higher than 1023 (2^10) it returns 1023 else it returns the level value
	if(level > 1023) return 1023;
	else return level;
}

/// <summary>
/// 8 bit clipping function
/// It returns the level of the input after clipping.
/// </summary>
/// <param name="level">Value to clip on 8 bits</param>
uint16_t clip8(uint16_t level)
{
	//	If the level value is higher than 1023 (2^10) it returns 1023 else it returns the level value
	if(level > 255) return 255;
	else return level;
}

/// <summary>
/// PWM0 Initialization function
/// </summary>
void InitPWM0()
{
	pwm0_level = 0;
	avrPrintf("PWM 0 Not implemented\r\n");
}

/// <summary>
/// PWM1 Initialization function
/// </summary>
void InitPWM1()
{
	pwm1_level = 0;
	avrPrintf("PWM 1 Not implemented\r\n");
}

/// <summary>
/// PWM2 Initialization function
/// </summary>
void InitPWM2()
{
	pwm2_level = 0;
	//avrPrintf("PWM 2 Not implemented\r\n");
	//	Configure the PWM2 pin in output mode
	pinMode(PWM2_OUT_PIN, OUTPUT);
}

/// <summary>
/// PWM3 Initialization function
/// </summary>
void InitPWM3()
{
	pwm3_level = 0;
	avrPrintf("PWM 3 Not implemented\r\n");
}

/// <summary>
/// PWM4 Initialization function
/// </summary>
void InitPWM4()
{
	#ifdef DEBUG
	avrPrintf("Entering InitPWM4...\r\n");
	#endif // DEBUG
	//	Configure the PWM4 pin in output mode
	pinMode(PWM4_OUT_PIN, OUTPUT);
}

/// <summary>
/// PWM0 Initialization function
/// </summary>
/// <param name="level">PWM0 new level value</param>
void SetPWM0(uint8_t level)
{
	//	Clip the desired value on 8 bits and store it
	pwm0_level = clip8(level);
}

/// <summary>
/// PWM1 Initialization function
/// </summary>
/// <param name="level">PWM1 new level value</param>
void SetPWM1(uint8_t level)
{
	//	Clip the desired value on 8 bits and store it
	pwm1_level = clip8(level);
}

/// <summary>
/// PWM2 Initialization function
/// </summary>
/// <param name="level">PWM2 new level value</param>
void SetPWM2(uint8_t level)
{
	//	Clip the desired value on 8 bits and store it
	pwm2_level = clip8(level);
	//	Update the PWM level
	analogWrite(PWM2_OUT_PIN, pwm2_level);
}

/// <summary>
/// PWM3 Initialization function
/// </summary>
/// <param name="level">PWM3 new level value</param>
void SetPWM3(uint8_t level)
{
	//	Clip the desired value on 8 bits and store it
	pwm2_level = clip8(level);
	//	Update the PWM level
	//analogWrite(PWM2_OUT_PIN, pwm2_level);
}

/// <summary>
/// PWM4 Initialization function
/// </summary>
/// <param name="level">PWM4 new level value</param>
void SetPWM4(uint8_t level)
{
	#ifdef DEBUG
	avrPrintf("Entering SetPWM4 Set...\r\n");
	#endif // DEBUG
	
	//	Clip on 8 bits the level value before
	pwm4_level = clip8(level);
	//	Update the PWM level
	analogWrite(PWM4_OUT_PIN, pwm4_level);
}

/// <summary>
/// Shell PWM  Initialization command.
///  This is the implementation of the shell command pwm_init, it initializes a PWM channel
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void vPwmInit(int argc, char *argv[])
{
	#ifdef DEBUG
	avrPrintf("Entering vPWMInit...\r\n");
	avrPrintf("argv[0] -> "); avrPrintf(argv[0]); avrPrintf(CR);
	avrPrintf("argv[1] -> "); avrPrintf(argv[1]); avrPrintf(CR);
	#endif // DEBUG
	
	//	If the number of arguments is not 1 report an error and show how to use the command
	//if (argc < 1)
	if (argc != 1)
	{
		vUsage("pwm_init <PWM Channel>");
	}
	else
	{
		//	Otherwise convert the first parameter from char to number
		uint8_t channel = atoi(argv[0]);		
		if ((channel >= 0) && (channel <= 4))
		{
			//	If the channel is between 0 and 4 decode it and launch the corresponding function, with an ACK at the end
			//	The function is launched only if the corresponding PWM channel is available
			switch(channel)
			{
				case 0: if (PWM0_AVAILABLE)
					{
						InitPWM0();
						avrPrintf("OK\r\n");
					}
					break;
				case 1: if (PWM1_AVAILABLE)
					{
						InitPWM1();
						avrPrintf("OK\r\n");
					}
					break;
				case 2: if (PWM2_AVAILABLE)
					{
						InitPWM2();
						avrPrintf("OK\r\n");
					}
					break;
				case 3: if (PWM3_AVAILABLE)
					{
						InitPWM3();
						avrPrintf("OK\r\n");
					}
					break;
				case 4: if (PWM4_AVAILABLE)
					{
						InitPWM4();
						//avrPrintf("Passed to InitPWM4\r\n");
						avrPrintf("OK\r\n");
					}
					break;
				default:
					//	Shouldn't pass here just in case report an error message
					avrPrintf("Error: Bad PWM channel!\r\n");
					vUsage("pwm_init <PWM Channel>");
					break;
			}				
		}		
		//	Found an invalid channel, report an error
		else avrPrintf("Error: Bad PWM Channel\r\n");
	}	
}

/// <summary>
/// Shell PWM  Start command.
///  This is the implementation of the shell command pwm_start, it starts a PWM channel
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void vPwmStart(int argc, char *argv[])
{
	#ifdef DEBUG
	avrPrintf("Entering vPwmStart...\r\b");
	#endif // DEBUG
	
	//	If the number or arguments is not 1 report an error message and show how to use the command
	if(argc != 1)
	//if (argc < 1)
	{
		vUsage("pwm_start <pwm channel>");
	}
	else
	{
		//	Otherwise convert the channel from char to numeric value
		uint8_t ch = (uint8_t)atoi(argv[0]); 
		//	Decode the channel value, and launch the corresponding PWM Start funcion
		switch (ch)
		{
			case 0: if(PWM0_AVAILABLE)
				{
					Pwm0_Start();
					avrPrintf("OK\r\n");
				}				 
				break;
			case 1: if (PWM1_AVAILABLE)
				{
					Pwm1_Start();
					avrPrintf("OK\r\n");
				}
				break;
			case 2: if(PWM2_AVAILABLE)
				{
					Pwm2_Start();
					avrPrintf("OK\r\n");
				}
				break;
			case 3: if(PWM3_AVAILABLE)
				{
					Pwm3_Start();
					avrPrintf("OK\r\n");
				}
				break;
			case 4: if (PWM4_AVAILABLE)
				{
					Pwm4_Start(); 
					avrPrintf("OK\r\n");
				}
				break;
				//	If a channel is not between 0 and 4 it reports an error message
			default: avrPrintf("Error: PWM Channel not valid\r\n");
				break;
		}			
	}
	//avrPrintf("OK\r\n");
}

/// <summary>
/// Shell PWM  Stop command.
///  This is the implementation of the shell command pwm_stop, it stops a PWM channel
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void vPwmStop(int argc, char *argv[])
{
	#ifdef DEBUG
	avrPrintf("Entering vPwmStop...\r\b");
	#endif // DEBUG
	
	//	If the number of arguments is not 1 report an error message a displayt how to use the command
	if(argc != 1)
	//if (argc < 1)
	{
		vUsage("pwm_stop <pwm channel>");
	}
	else
	{
		//	Otherwise convert the channel from char to numeric value
		uint8_t ch = atoi(argv[0]);
		//	Decode the channel value and launch the corresponding stop function if the channel is available
		switch(ch)
		{
			case 0: if (PWM0_AVAILABLE)
				{
					Pwm0_Stop();
					avrPrintf("OK\r\n");	
				}
				break;
			case 1: if(PWM1_AVAILABLE)
				{
					Pwm1_Stop();
					avrPrintf("OK\r\n");
				}
				break;
			case 2: if (PWM2_AVAILABLE)
				{
					Pwm2_Stop();
					avrPrintf("OK\r\n");
				}
				break;
			case 3: if (PWM3_AVAILABLE)
				{
					Pwm3_Stop();
					avrPrintf("OK\r\n");
				}
				break;
			case 4: if (PWM4_AVAILABLE)
				{
					Pwm4_Stop();
					avrPrintf("OK\r\n");
				}
				break;
				//	If none of the above report an error message
			default: avrPrintf("Error: invalid PWM Channel\r\n"); break;
		}		
	}
}

/// <summary>
/// Shell PWM  Setting command.
///  This is the implementation of the shell command pwm_set, it sets a PWM channel to a new value
/// </summary>
/// <param name="argc">Number of parameters</param>
/// <param name="argv">List of parameters</param>
void vPwmSet(int argc, char *argv[])
{
	#ifdef DEBUG
	avrPrintf("Entering vPWMSet...\r\n");
	#endif // DEBUG
	
	//	If the number of parameters is different than 2 there is an error, then display the usage
	if (argc != 2)
	{
		vUsage("pwm_set <PWM Channel> <value>");
	}
	else
	{
		//	Checks if the first parameters is a valid PWM channel (between 0 and 4)
		if ((*argv[1] >= '0') && (*argv[1] <= '4'))
		{
			//	If yes convert it first from char to numeric value
			uint8_t channel = atoi(argv[0]);
			uint16_t level = atoi(argv[1]);
			//	Then select the PWM channel and launch the corresponding action for that channel
			switch(channel)
			{
				case 0: if (PWM0_AVAILABLE)
				{
					SetPWM0(level); 
					avrPrintf("OK\r\n");
				}					
				break;
				case 1: if(PWM1_AVAILABLE)
				{
					SetPWM1(level);
					avrPrintf("OK\r\n");
				}
				break;
				case 2: if(PWM2_AVAILABLE)
				{
					SetPWM2(level);
					avrPrintf("OK\r\n");
				}
				break;
				case 3: if(PWM3_AVAILABLE)
				{
					SetPWM3(level);
					avrPrintf("OK\r\n");
				}
				break;
				case 4: if(PWM4_AVAILABLE)
				{
					SetPWM4(level);
					avrPrintf("OK\r\n");
				}
				break;	
				default:
				//	Shouldn't go there, in case report an error to the shell
				avrPrintf("Error: Bad PWM channel!\r\n");
				vUsage("pwm_init <PWM Channel>");
				break;
			}
		}
	}	
	//	Display an ACK to the shell that everything is fine
	avrPrintf("OK\r\n");
}

/// <summary>
/// PWM0 Starting function.
/// </summary>
void Pwm0_Start()
{
	
}

/// <summary>
/// PWM1 Starting function.
/// </summary>
void Pwm1_Start()
{
	
}

/// <summary>
/// PWM2 Starting function.
/// </summary>
void Pwm2_Start()
{
	
}

/// <summary>
/// PWM3 Starting function.
/// </summary>
void Pwm3_Start()
{
	
}

/// <summary>
/// PWM4 Starting function.
/// </summary>
void Pwm4_Start()
{
	#ifdef DEBUG
	avrPrintf("Finalmente Starting PWM 4\r\n");
	#endif // DEBUG
	//	Start the PWM4 writing half the level
	analogWrite(PWM4_OUT_PIN, 127);
}

/// <summary>
/// PWM0 Stopping function.
/// </summary>
void Pwm0_Stop()
{
	
}

/// <summary>
/// PWM1 Stopping function.
/// </summary>
void Pwm1_Stop()
{
	
}

/// <summary>
/// PWM2 Stopping function.
/// </summary>
void Pwm2_Stop()
{
	
}

/// <summary>
/// PWM3 Stopping function.
/// </summary>
void Pwm3_Stop()
{
	
}

/// <summary>
/// PWM4 Stopping function.
/// </summary>
void Pwm4_Stop()
{
	#ifdef DEBUG
	avrPrintf("Starting PWM 4\r\n");
	#endif // DEBUG
	//	Write 0 to the PWM4 channel to shut it down
	analogWrite(PWM4_OUT_PIN, 0);
}

	

