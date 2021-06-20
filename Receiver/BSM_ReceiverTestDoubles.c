/******************************************************* Header_Files *******************************************************/ 

#include "SignalReceiver.h"
#include <string.h>

/******************************************* /MacroFunction/Variable Declarations *******************************************/ 

int scanf(char *format, char * InputBuffer);
int printf(char *format, float Temp_MinValue, float Temp_MaxValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MaxValue, float ChargeRate_MovingAvg);

char InputMessageBuf[15][100];
char* ConsoleInputFormat[15];
char* ConsoleInputValue[15];
char* ConsoleOutputFormat[15];
float	ConsoleOutputTemperatureMin[15];
float	ConsoleOutputTemperatureMax[15];
float	ConsoleOutputTemperatureMovingAvg[15];
float	ConsoleOutputChargeRateMin[15];
float	ConsoleOutputChargeRateMax[15];
float	ConsoleOutputChargeRateMovingAvg[15];
int printf_Func_CallCount=0;
int scanf_Func_CallCount=0;
int ResetScanfMsgIndex=1;
int ResetPrintfMsgIndex=1;


/*************************************************** function Definitions **************************************************/

int ResetTestInterface()
{
	printf_Func_CallCount=0;   // Resetting the Global variable
	scanf_Func_CallCount=0;  // Resetting the Global variable
	int ResetScanfMsgIndex=1;  // Resetting the static variable to avoid the array index over flow error
	int ResetPrintfMsgIndex=1; // Resetting the static variable to avoid the array index over flow error
	return 0;
}


int scanf(char *format, char * InputBuffer)
{ 
	static int MsgBufIndex=0;
		
	if(ResetScanfMsgIndex==1)
	{
		MsgBufIndex=0;  // Resetting the static variable to avoid the array index over flow error
		ResetScanfMsgIndex=0;
	}
	
	ConsoleInputFormat[MsgBufIndex]=format;
	strcpy(InputBuffer,InputMessageBuf[MsgBufIndex]);
	strcpy(ConsoleInputValue[MsgBufIndex],InputBuffer);
	
	scanf_Func_CallCount++;
	
	MsgBufIndex++;
	
	return 0;
}


int printf(char *format, float Temp_MinValue, float Temp_MaxValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MaxValue, float ChargeRate_MovingAvg)
{	
	static int MsgIndex=0;
	
	
	if(ResetPrintfMsgIndex==1)
	{
		MsgIndex=0;  // Resetting the static variable to avoid the array index over flow error
		ResetPrintfMsgIndex=0;
	}
		
	ConsoleOutputFormat[MsgIndex]=format;
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

