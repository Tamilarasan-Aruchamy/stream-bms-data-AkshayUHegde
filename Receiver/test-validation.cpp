#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test/catch.hpp"
#include "SignalProvider.h"
#include "BMS_TestDoublesHeader.h"
#include<stddef.h>
#include<string.h>

extern int BSM_SignalProvider(OutputTarget OutputTargetIndex);


TEST_CASE("Test the Number printf function calls") 
{
	ResetTestInterface();
	
	REQUIRE(BSM_SignalProvider(TO_CONSOLE)==0);
	REQUIRE(printf_Func_CallCount==15);
}

TEST_CASE("Test the output Format, Temperature and SOC") 
{
	float Temp_RandNum_Min=-30.0;
	float Temp_RandNum_Max=50.0;
	float SOC_RandNum_Min=20.0;
	float SOC_RandNum_Max=50.0;
	int Rand_Temperature[15]={0,1,2,3,4,5,6,7,RAND_MAX-7,RAND_MAX-6,RAND_MAX-5,RAND_MAX-4,RAND_MAX-3,RAND_MAX-2,RAND_MAX-1}; // Test data for rand() func return value
	int Rand_SOC[15]={0,1,2,3,4,5,6,7,RAND_MAX-7,RAND_MAX-6,RAND_MAX-5,RAND_MAX-4,RAND_MAX-3,RAND_MAX-2,RAND_MAX-1}; // Test data for rand() func return value
	
	ResetTestInterface(); // Reset the all mocks/stubs variables
	
	REQUIRE(BSM_SignalProvider(TO_CONSOLE)==0);
	for(int Itr=0;Itr<15;Itr++)
	{
	REQUIRE(strcmp(ConsoleOutputFormat[Itr],"{\"Temperature\":%0.2f,\"SOC\":%0.2f}\n")==0);
	REQUIRE(ConsoleOutputTemperature[Itr]==(float)((((float)(Rand_Temperature[Itr])/RAND_MAX)*(Temp_RandNum_Max-Temp_RandNum_Min))+Temp_RandNum_Min));
	REQUIRE(ConsoleOutputSOC[Itr]==(float)((((float)(Rand_SOC[Itr])/RAND_MAX)*(SOC_RandNum_Max-SOC_RandNum_Min))+SOC_RandNum_Min));
     	}
}

