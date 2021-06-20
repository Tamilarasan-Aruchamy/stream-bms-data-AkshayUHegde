/******************************************************* Header_Files *******************************************************/ 

#include "SignalReceiver.h"
#include <stddef.h>
#include <stdio.h>

/******************************************* /MacroFunction/Variable Declarations *******************************************/ 

int scanf(const char *format, char * InputBuffer)
int printf(const char *format, float Temp_MinValue, float Temp_MinValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MinValue, float ChargeRate_MovingAvg);

char InputMessageBuf[15][100];
char* ConsoleOutputFormat[15];
float	ConsoleOutputTemperatureMin[15];
float	ConsoleOutputTemperatureMax[15];
float	ConsoleOutputTemperatureMovingAvg[15];
float	ConsoleOutputChargeRateMin[15];
float	ConsoleOutputChargeRateMax[15];
float	ConsoleOutputChargeRateMovingAvg[15];
int printf_Func_CallCount=0;


/*************************************************** function Definitions **************************************************/

int ResetTestInterface()
{
	printf_Func_CallCount=0;   // Resetting the Global variable
	return 0;
}


int scanf(const char *format, char * InputBuffer)
{ 
	int Itr=0;
	InputBuffer=InputMessageBuf[Itr];
	Itr++;
	
	return 0;
}


int printf(const char *format, float Temp_MinValue, float Temp_MinValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MinValue, float ChargeRate_MovingAvg)
{	
	static int MsgIndex=0;
	
	
	if(MsgIndex>=15)
	{
		MsgIndex=0;  // Resetting the static variable to avoid the array index over flow error
	}
		
	ConsoleOutputFormat[MsgIndex]=Format;
	ConsoleOutputTemperatureMin[MsgIndex]=Temp_MinValue;
	ConsoleOutputTemperatureMax[MsgIndex]=Temp_MaxValue;
	ConsoleOutputTemperatureMovingAvg[MsgIndex]=Temp_MovingAvg;
	ConsoleOutputChargeRateMin[MsgIndex]=ChargeRate_MinValue;
	ConsoleOutputChargeRateMax[MsgIndex]=ChargeRate_MaxValue;
	ConsoleOutputChargeRateMovingAvg[MsgIndex]=ChargeRate_MovingAvg;

	printf_Func_CallCount++;
	
	MsgIndex++;

	return 0;
}

