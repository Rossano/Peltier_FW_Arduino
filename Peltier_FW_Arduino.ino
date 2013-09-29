//----------------------------------------------------------------------------------------//
//					Peltier_FW_Arduino.ino							//
//																//
//----------------------------------------------------------------------------------------//
//																//
//	Firmware for the¨Peltier Cell control using an Arduino platform.				//
//	This software does not include an OS.									//
//																//
//	Version 1.0													//
//	Copyright Rossano Pantaleoni 2013									//
//---------------------------------------------------------------------------------------//


//#define	SOL_LED			13
#define CMD_STRING_LEN	16
#define PROMPT			"AVR> "

//	My include file
#include "board.c"
#include "shell.c"
#include "adc.c"
#include "pwm.c"

//
//	Function prototypes
//
void setup();
void loop();
void CDC_Task();

//
//	Global Data
//
String cmdString = "";				//	Line Command string buffer
boolean cmdReady = false;			//	Flag indicating that a command is ready
uint8_t inBufCount = 0;				//	Input buffer char counter

//
//	Arduino Initialization Function
//
void setup()
{

  /* add setup code here */
  
	//
	//	Initialize the board, setting up all the I/O in a known state
	//
	initBoard();
	//pinMode(SOL_LED, OUTPUT);
	
	//	Initialize the USB link for PC communication
	Serial.begin(9600);
	//	Reserve space for the command line string buffer
	cmdString.reserve(CMD_STRING_LEN);
	//
	//	Until the USB CDC is not connected to the PC the yellow LED on Arduino is 
	//	blinking, then it will be fix
	//
	while(!Serial)
	{
		digitalWrite(SOL_LED, HIGH);
		delay(300);
		digitalWrite(SOL_LED, LOW);
		delay(300);
	}
	
	//digitalWrite(SOL_LED,HIGH);
	
	//	Highlight the LED in PWM mode to allow the hard fix the light level
	analogWrite(SOL_LED, 32);
	//	Write the prompt on serial link
	Serial.print(PROMPT);
}

//
//	Arduino Loop function
//
void loop()
{

  /* add main program code here */

	char ch;
	
	//	Execute the USB-CDC task
	CDC_Task();
	//
	//	If the '\n' is received the flag cmdReady is set and the input string is consumed by the Shell
	//
	if (cmdReady)
	{
		#ifdef DEBUG
		Serial.println("Received -> " + cmdString);
		#endif // DEBUG
		
		char buffer[CMD_STRING_LEN];		
		//	Create the char buffer pointer for the shell
		char *buf = (char *)&buffer;
		cmdString.toCharArray(buf, CMD_STRING_LEN);
		//	Execute the Shell task with the data coming for the PC
		ShellTask((void *)ShellCommand, buf);
		//	Print the prompt
		Serial.print(PROMPT);
		//	Reinitialize the input buffer and the flag
		cmdString = "";
		cmdReady = false;
		inBufCount = 0;
	}
}

//
//	USB-CDC Task
//
void CDC_Task()
{
	char ch;
	//
	//	Until data are available from the Serial Port read the data and store it into the input buffer cmdString
	//	Process ends if '\n' is received or the MAX input string length is reached
	//
	while(Serial.available())
	{
		//	If '\n" is received or MAX string lenght is reached set the cmdReady flag
		if (++inBufCount == CMD_STRING_LEN) ch = '\n';
		else
		{
			ch = (char)Serial.read();
			cmdString += ch;	
		}				
		if (ch == '\n') cmdReady = true;		
	}	
}

//
//	Printf function for AVR:
//	Need to be at this level to be visible to all the moduls
//
void avrPrintf(const char * str)
{
	#ifdef __AVR_SIMULATION__
	//	PC simulated
	printf("%s", str);
	#else
	//	Print the string str
	Serial.print(str);
	#endif
}