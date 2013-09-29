//----------------------------------------------------------------------------------------//
//							shell.h								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

#ifndef _SHELL_h
#define _SHELL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//
//	Definitions sections
//
#define NULL						0		//	NULL definition (error trying to include from elsewhere
#define SHELL_MAX_LINE_LENGTH       16		//	Shell input buffer length
#define SHELL_MAX_ARGUMENTS         4		//	Shell MAX number of arguments
#define SHELL_PROMPT                "AVR> "	//	Shell prompt
#define FW_VERSION                  "1.0.0"	//	Firmware Revision
#define OS_VERSION                  "N/A"	//	OS type and revision
#define CR							"\r\n"	//	Shell EOL characters

//	Function prototype for the action executed by the shell
typedef void (* shellcmd_t)(int argc, char *argv[]);

//
//	Actions to be executed by the shell defined in different files
//
extern void ADCInit(int argc, char *argv[]);			//	Initialize the ADC
extern void getADC_Result(int argc, char *argv[]);		//	Read from the ADC
extern void vPwmInit(int argc, char *argv[]);			//	Initialize a PWM
extern void vPwmStart(int argc, char *argv[]);			//	Start a PWM
extern void vPwmStop(int argc, char *argv[]);			//	Stop a PWM
extern void vPwmSet(int argc, char *argv[]);			//	Set the level of a PWM

//
//	Shell Command Data type:
//	Struct composed by the name of the command and a function prototype for the action to execute
//
typedef struct
{
	const char *sc_name;
	shellcmd_t  sc_function;
} ShellCommand_t;

//
//	Shell Configuration data type (don't think it is used)
//
typedef struct
{
	const ShellCommand_t *sc_command;
} ShellConfig_t;

//
//	Local Actions of the Shell
//
void vSendACK(int argc, char *argv[]);					//	Send back a ACK to the PC
void vCmdInfo(int argc, char *argv[]);					//	Get back the info about the FW revision
void vCmdSystime(int argc, char *argv[]);				//	Command system time (not implemented)

//xShellCommand_t xLocalCommands[] =
//{
//{
//"info", vCmdInfo
//},
//{
//"systime", vCmdSystime
//},
//{
//NULL, NULL
//}
//};

//
//	Definition of the shell commands:
//	This data structure links the command to the corrisponding action function
//
static ShellCommand_t ShellCommand[] =
{
	{
		"get_ACK",	vSendACK
	},
	{
		"pwm_init", vPwmInit
	},
	{
		"pwm_start", vPwmStart
	},
	{
		"pwm_stop", vPwmStop
	},
	{
		"pwm_set", vPwmSet
	},
	{
		"adc_init", ADCInit
	},
	{
		"adc_get", getADC_Result
	},
	{
		NULL, NULL
		//(char *)0, (void **)0
	}
} ;

//	Configuration data structure
ShellConfig_t ShellConfig;

//
//	Function prototypes for the shell.c
//
void vShellThread (void *p);
char * vStrtok(char *str, const char *delim, char **saveptr);
//static void vUsage(char *str);
//static int vCmdExec(const xShellCommand_t *scp, char *name, int argc, char *argv[]);
//static void vListCommands(xShellCommand_t *scp);
void vUsage(char *str);
int vCmdExec(const ShellCommand_t *scp, char *name, int argc, char *argv[]);
void vListCommands(ShellCommand_t *scp);
void avrPrintf(const char * str);
void ShellTask(void *p, char *line);


#endif

