//----------------------------------------------------------------------------------------//
//							shell.c								//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	Entry point for the AVR console application. The shell has the task to receive	//
//	a command and execute the associated command.						//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//

#undef __AVR_SIMULATION__
#undef __VS_CPP__

#ifdef __AVR_SIMULATION__ //&& __VS_C++__)
#include "stdafx.h"
#else
#include <string.h>
#include <stdio.h>
#endif

//	My included file and headers
#include <stddef.h>
#include "adc.h"
#include "pwm.h"

#ifndef __AVR_SIMULATION__
//#include "VirtualSerial.h"
#endif

//	Shell own inclusion header
#include "shell.h"

//	???
static boolean bEnd = false;

//
//	Shell Local command definition data structure
//
static ShellCommand_t LocalCommands[] =
{
	{
		"info", vCmdInfo
	},
	{
		"systime", vCmdSystime
	},
	{
		NULL, NULL
	}
};

/// <summary>
/// Shells  task code.
/// </summary>
/// <param name="p">Pointer to a data structure storing all implemented commands</param>
/// <param name="line">The commanbd line.</param>
void ShellTask(void *p, char *line)
{
	int n;
	//	Initialize the shell command data structure
	const ShellCommand_t *scp=((ShellConfig_t *)p)->sc_command;
	char *lp, *cmd, *tokp;
	char *args[SHELL_MAX_ARGUMENTS + 1];

	//	Get all the tokens from the input string and stores them on lp and tokp pointer
	lp = vStrtok(line, " \r\n", &tokp);
	
	#ifdef DEBUG
	avrPrintf("lp -> ");
	avrPrintf(lp);
	avrPrintf("\ntokp -> ");
	avrPrintf(tokp);
	avrPrintf(CR);
	#endif // DEBUG
	
	//	The command to execute is stored into lp
	cmd = lp;
	n = 0;
	
	//
	//	Until there are valid tokens fill the arguments array args with them
	//
	while ((lp = vStrtok(NULL, " \r\n", &tokp)) != NULL)
	{
		//	If there are too many arguments display an error
		if (n > SHELL_MAX_ARGUMENTS)
		{
			avrPrintf ("Too many arguments\r\n");
			cmd = NULL;
			break;
		}
		// else fill arguments array
		args[n++] = lp;
	}
	//	End the args array with a NULL argument
	args[n] = NULL;
	// do we really need it ???? 
	if (n == 0)
	{
		#ifdef DEBUG
		avrPrintf("Forcing end of string\r\n");
		#endif // DEBUG		
		int len = strlen(cmd);
		cmd[len] = '\0';
	}
	
	#ifdef DEBUG
	avrPrintf("Cmd -> ");
	avrPrintf(cmd);
	avrPrintf(CR);
	char numArgv[2];
	numArgv[0] = '0' + n;
	numArgv[1] = '\0';
	avrPrintf("n -> ");
	avrPrintf(numArgv);
	avrPrintf(CR);
	#endif // DEBUG
	
	//
	//	If there is a valid command to execute (not NULL),parse it and execute the corresponding action
	//
	if (cmd != NULL)
	{		
		//	Exit the Shell
		if (strcasecmp(cmd, "exit") == 0)
		{
			//	Exit has no arguments
			if (n > 0)
			{
				vUsage("exit");
			}
			// Set the shell end flag
			bEnd = true;
			return; 
		}
		//	Display the list of supported commands
		else if (strcasecmp(cmd, "help") == 0)
		{
			//	Help has no arguments
			avrPrintf("Entering help\r\n");
			if (n > 1)
			{
				vUsage("help");		
			}
			avrPrintf("Commands:\r\n");
			//	Display the Local Commands
			vListCommands(LocalCommands);
			//	Display the Shell Commands
			vListCommands(ShellCommand);
			avrPrintf(CR);
		}
		//	Try to Execute the other command, if it exits an error the command is not recognized
		else if (vCmdExec(LocalCommands, cmd, n, args) && ((scp == NULL) || vCmdExec(/*scp*/ ShellCommand, cmd, n, args)))
		{
			avrPrintf("Error: Command not recognized -> ");
			avrPrintf (cmd);
			avrPrintf (" ???\r\n");
		}
	}
}

/// <summary>
/// Shell thread loop.
/// this function read from stdin and calls the real thread code
/// </summary>
/// <param name="p">A pointer to the implemented commands.</param>
void vShellThread(void *p)
{
	char line[SHELL_MAX_LINE_LENGTH];
	// chRegSetThreadName("shell");

	avrPrintf("\r\nAVR Shell;\r\n");

	while (!bEnd)
	{
		// Display the prompt
		avrPrintf(SHELL_PROMPT);
		// Get the command line from stdin
		gets(line);
		// Calls the shell task
		ShellTask(p, line);
	}
	return;
}

/// <summary>
/// Command Execution.
/// Execute a command and return the result.
/// </summary>
/// <param name="scp">A pointer to the implemented commands.</param>
/// <param name="name">Name of the command to execute</param>
/// <param name="argv">A pointer to the Argument list.</param>
int vCmdExec(const ShellCommand_t *scp, char *name, int argc, char *argv[])
{
	while (scp->sc_name != NULL)
	{
		if(strcmp(scp->sc_name, name) == 0)
		{
			scp->sc_function(argc, argv);
			return 0;
		}
		scp++;
	}
	return 1;
}

/// <summary>
/// System Time Command.
/// Not implemented.
/// </summary>
/// <param name="argc">Number of parameters.</param>
/// <param name="argv">A pointer to the Argument list.</param>
void vCmdSystime(int argc, char *argv[])
{
	(void) argv;
	//	If there are arguments display and error message
	if(argc > 0)
	{
		vUsage("systime");
		return;
	}
	//	Else display a string stating that it is not implemented
	avrPrintf("Sys Time: Not implemented yet\r\nOK\r\n");
}

/// <summary>
/// Info Command.
/// Display firmware information.
/// </summary>
/// <param name="argc">Number of parameters.</param>
/// <param name="argv">A pointer to the Argument list.</param>

void vCmdInfo(int argc, char *argv[])
{
	(void)argv;
	//	If there are arguments plot an error message
	if(argc > 1)
	{
		vUsage("info");
		return;
	}
	//	Else display Firmware and OS versions
	avrPrintf("Firmware: ");
	avrPrintf(FW_VERSION);
	avrPrintf("\r\nOS Version: ");
	avrPrintf(OS_VERSION);
	avrPrintf("\r\nOK\r\n");
}

/// <summary>
/// List the Commands in the scp data structure.
/// </summary>
/// <param name="scp">Command data structure.</param>
void vListCommands(ShellCommand_t *scp)
{
	//	Until the commands data structure has valid elements display the command name
	while (scp->sc_name != NULL)
	{
		avrPrintf((char *)scp->sc_name);
		avrPrintf("\r\n");
		scp++;
	}
}

/// <summary>
/// Command Usage Function.
/// Display information how to use the command.
/// </summary>
/// <param name="strc">Command usage string.</param>
void vUsage(char *str)
{
	avrPrintf("Error: Usage-> ");
	avrPrintf(str);
	avrPrintf("\r\n");
}

/// <summary>
/// Substring token extraction.
/// </summary>
/// <param name="strc">Input string.</param>
/// <param name="delim">String containing a list of delimiters.</param>
/// <param name="saveptr">Vector of String containing all the substrings.</param>
char * vStrtok(char *str, const char *delim, char **saveptr)
{
	char *token;
	if (str) *saveptr = str;
	token = *saveptr;

	if (!token) return NULL;

	token += strspn(token, delim);
	*saveptr = strpbrk(token, delim);

	if (*saveptr) *(*saveptr)++ = '\0';

	return *token ? token : NULL;
}

/// <summary>
/// Send the ACK
/// </summary>
/// <param name="argc">Number of parameters.</param>
/// <param name="argv">A pointer to the Argument list.</param>
void vSendACK(int argc, char *argv[])
{
	//	If there are arguments send an error message
	if (argc > 0)
	{
		vUsage("get_ACK");
	}
	else
	{
		//	Send the ACK
		avrPrintf("ACK\r\nOK\r\n");
	}
}

//
//	Only needed when simulating the AVR on PC
//
#ifdef __AVR_SIMULATION__
int _tmain(int argc, _TCHAR* argv[])
{
	vShellThread((void *)xShellCommand);

	return 0;
}
#endif


