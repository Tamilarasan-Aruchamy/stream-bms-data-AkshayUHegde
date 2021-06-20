/******************************************************* Header_Files *******************************************************/ 

#include "SignalReceiver.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

/******************************************* /MacroFunction/Variable Declarations *******************************************/ 

int scanf(char* Format, char * InputBuffer)
int printf(char* Format, float Temp_MinValue, float Temp_MinValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MinValue, float ChargeRate_MovingAvg);

char* ConsoleOutputFormat[15];
float	ConsoleOutputTemperatureMin[MsgIndex];
float	ConsoleOutputTemperatureMax[MsgIndex];
float	ConsoleOutputTemperatureMovingAvg[MsgIndex];
float	ConsoleOutputChargeRateMin[MsgIndex];
float	ConsoleOutputChargeRateMax[MsgIndex];
float	ConsoleOutputChargeRateMovingAvg[MsgIndex];
int printf_Func_CallCount=0;


/*************************************************** function Definitions **************************************************/

int ResetTestInterface()
{
	printf_Func_CallCount=0;   // Resetting the Global variable
	return 0;
}


int scanf(char* Format, char * InputBuffer)
{ 
	int Rand_Temperature[15]={0,1,2,3,4,5,6,7,RAND_MAX-7,RAND_MAX-6,RAND_MAX-5,RAND_MAX-4,RAND_MAX-3,RAND_MAX-2,RAND_MAX-1};
	int Rand_SOC[15]={0,1,2,3,4,5,6,7,RAND_MAX-7,RAND_MAX-6,RAND_MAX-5,RAND_MAX-4,RAND_MAX-3,RAND_MAX-2,RAND_MAX-1};
	
	static int Itr=0;
	int RandomValue=0;
	
	if(Itr>=30)
	{
		Itr=0;  // Resetting the static variable to avoid the array index over flow error
	}
	
	
	if(!(Itr%2))
	{
		RandomValue=Rand_Temperature[Itr/2];
		Itr++;
	}
	else
	{
		RandomValue=Rand_SOC[Itr/2];
		Itr++;
	}
	
	return RandomValue;
}


int printf(char* Format, float Temp_MinValue, float Temp_MinValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MinValue, float ChargeRate_MovingAvg)
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

