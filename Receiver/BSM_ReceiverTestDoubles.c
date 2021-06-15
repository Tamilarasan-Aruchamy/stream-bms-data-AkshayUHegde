/******************************************************* Header_Files *******************************************************/ 

#include "SignalProvider.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

/******************************************* /MacroFunction/Variable Declarations *******************************************/ 

#define RAND_MAX INT_MAX

int rand();
int printf(char* Format, float Temperature, float SOC);

char* ConsoleOutputFormat[15];
float ConsoleOutputTemperature[15];
float ConsoleOutputSOC[15];
int printf_Func_CallCount=0;


/*************************************************** function Definitions **************************************************/

int ResetTestInterface()
{
	printf_Func_CallCount=0;   // Resetting the Global variable
	return 0;
}


int rand()
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


int printf(char* Format, float Temperature, float SOC)
{	
	static int MsgIndex=0;
	
	
	if(MsgIndex>=15)
	{
		MsgIndex=0;  // Resetting the static variable to avoid the array index over flow error
	}
		
	ConsoleOutputFormat[MsgIndex]=Format;
	ConsoleOutputTemperature[MsgIndex]=Temperature;
	ConsoleOutputSOC[MsgIndex]=SOC;

	printf_Func_CallCount++;
	
	MsgIndex++;

	return 0;
}

