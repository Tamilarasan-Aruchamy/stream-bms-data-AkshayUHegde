#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test/catch.hpp"
#include "SignalReceiver.h"
#include "BMS_ReceiverTestDoublesHeader.h"
#include <string.h>
#include <stdlib.h>

extern int BSM_SignalReceiver();

class Assert {

  public:
    void AssertOutput(int,MinMaxAvg*);
};


TEST_CASE("Test the Func Call,Min, Max and Avg") 
{
	ResetTestInterface();
	Assert Output;
	char BSM_InputMessage_TestData_1[15][100]={"{\"charge_rate\": 18.69, \"temp_in_c\": 5.26}",\
                                    "{\"charge_rate\": 9.69, \"temp_in_c\": 6.26}",\
                                    "{\"charge_rate\": 10.69, \"temp_in_c\": 21.26}",\
                                    "{\"charge_rate\": 30.69, \"temp_in_c\": 8.26}",\
                                    "{\"charge_rate\": 12.69, \"temp_in_c\": 9.26}",\
                                    "{\"charge_rate\": 13.69, \"temp_in_c\": 10.26}",\
                                    "{\"charge_rate\": 14.69, \"temp_in_c\": 11.26}",\
                                    "{\"charge_rate\": 15.69, \"temp_in_c\": 12.26}",\
                                    "{\"charge_rate\": 16.69, \"temp_in_c\": 13.26}",\
                                    "{\"charge_rate\": 17.69, \"temp_in_c\": 14.26}",\
                                    "{\"charge_rate\": 18.69, \"temp_in_c\": 15.26}",\
                                    "{\"charge_rate\": 19.69, \"temp_in_c\": 16.26}",\
                                    "{\"charge_rate\": 20.69, \"temp_in_c\": 17.26}",\
                                    "{\"charge_rate\": 21.69, \"temp_in_c\": 18.26}",\
                                    "{\"charge_rate\": -22.69, \"temp_in_c\": 19.26}"};
	
					/* charge_rate {Min,Max and Avg}  Temp  {Min,Max and Avg} */
	MinMaxAvg Expected_MinMaxAvg[15][2]={{{18.69,18.69,3.738000},{5.26,5.26,1.052000}},\
						{{9.69,18.69,5.676000},{5.26,6.26,2.304000}},\
					       {{9.69,18.69,7.814000},{5.26,21.26,6.556000}},\
					       {{9.69,30.69,13.952001},{5.26,21.26,8.208000}},\
					       {{9.69,30.69,16.490002},{5.26,21.26,10.060000}},\
					       {{9.69,30.69,15.490001},{5.26,21.26,11.060000}},\
					       {{9.69,30.69,16.490002},{5.26,21.26,12.060000}},\
					       {{9.69,30.69,17.490002},{5.26,21.26,10.260000}},\
					       {{9.69,30.69,14.690001},{5.26,21.26,11.260000}},\
					       {{9.69,30.69,15.690001},{5.26,21.26,12.260000}},\
					       {{9.69,30.69,16.690001},{5.26,21.26,13.260000}},\
					       {{9.69,30.69,17.690001},{5.26,21.26,14.260000}},\
					       {{9.69,30.69,18.690001},{5.26,21.26,15.260000}},\
					       {{9.69,30.69,19.690001},{5.26,21.26,16.260000}},\
					       {{-22.69,30.69,11.614000},{5.26,21.26,17.208000}}};
	
	for(int i=0;i<15;i++)
		{
		  strcpy(InputMessageBuf[i],BSM_InputMessage_TestData_1[i]);
		}
	
	REQUIRE(BSM_SignalReceiver()==0);
	REQUIRE(scanf_Func_CallCount==15);
	REQUIRE(printf_Func_CallCount==15);
	
	for(int itr=0;itr<15;itr++)
		{
		 Output.AssertOutput(itr, Expected_MinMaxAvg[itr]);	 // Validate all parameters
		}
	
	
}

TEST_CASE("Test the wrong Input Message") 
{
	ResetTestInterface();
	Assert Output;
	char BSM_InputMessage_TestData_2[15][100]={"{\"charge_rate\": 8.69, \"temp_in_c\": 15.26}",\
                                    "{\"charge_ratee\": 1.69, \"temp_in_c\": 16.26}",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 2.69, \"temp_in_ca\": 121.26}",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 3.69, \"temp_in_c\": 18.26}",\
                                    "{\"charge_rate\": 4.69, \"temp_in_c\": 19.26}",\
                                    "{\"charge_rate\": 5.69, \"temp_in_c\": 110.26}",\
                                    "{\"charge_rate\": 6..69, \"temp_in_c\": 111.26}",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 7.69, \"temp_in_c\": 112.26}",\
                                    "{\"charge_rate\": 8.69, \"temp_in_c\": 113.26}",\
                                    "{\"charge_rate\": 9.69, \"temp_in_c\": b114.26}",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 10.69, \"temp_in_c\": 115.26}",\
                                    "\"charge_rate\": 11.69, \"temp_in_c\": 116.26}",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 12.69, \"temp_in_c\": 11-7.26}",  /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 13.69, \"temp_in_c\": 118.26",   /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ \
                                    "{\"charge_rate\": 14.69, \"temp_in_c\": 19.26 \"voltage\": 19.26}"};  /* Invalid Message. this will not consisder for Min,Max and Avg calculation */ 
	
					/* charge_rate {Min,Max and Avg}  Temp  {Min,Max and Avg} */
	MinMaxAvg Expected_MinMaxAvg[8][2]={{{8.69,8.69,1.738000},{15.26,15.26,3.052000}},\
						{{3.69,8.69,2.476000},{15.26,18.26,6.704000}},\
					       {{3.69,8.69,3.414000},{15.26,19.26,10.556000}},\
					       {{3.69,8.69,4.552000},{15.26,110.26,32.608002}},\
					       {{3.69,8.69,6.090000},{15.26,112.26,55.060005}},\
					       {{3.69,8.69,6.090000},{15.26,113.26,74.660004}},\
					       {{3.69,10.69,7.490000},{15.26,115.26,94.060005}}};
	
	for(int i=0;i<15;i++)
		{
		  strcpy(InputMessageBuf[i],BSM_InputMessage_TestData_2[i]);
		}
	
	REQUIRE(BSM_SignalReceiver()==0);
	REQUIRE(printf_Func_CallCount==8);
	REQUIRE(scanf_Func_CallCount==15);
	
	for(int i=0;i<15;i++)
		{
		  REQUIRE(strcmp(ConsoleScanfFormat[i],"%[^\n]%*c")==0);
		}
	
	for(int itr=0;itr<8;itr++)
		{
		  Output.AssertOutput(itr, Expected_MinMaxAvg[itr]); 	 // Validate all parameters	
		}
	
}


void Assert :: AssertOutput(int Index,MinMaxAvg* Expected_MinMaxAvg)
{
	REQUIRE(strcmp(ConsoleScanfFormat[Index],"%[^\n]%*c")==0);
	
	REQUIRE(strcmp(ConsolePrintfFormat[Index],"ChargeRateMin:%0.2f ChargeRateMax:%0.2f ChargeRateAvg:%0.2f TempMin:%0.2f TempMax:%0.2f TempAvg:%0.2f\n")==0);

	REQUIRE(ConsoleOutputChargeRateMin[Index]==Expected_MinMaxAvg[0].MinValue);
	REQUIRE(ConsoleOutputChargeRateMax[Index]==Expected_MinMaxAvg[0].MaxValue);
	REQUIRE(abs(ConsoleOutputChargeRateMovingAvg[Index]-Expected_MinMaxAvg[0].MovingAvg)<0.1);
	
	REQUIRE(ConsoleOutputTemperatureMin[Index]==Expected_MinMaxAvg[1].MinValue);
	REQUIRE(ConsoleOutputTemperatureMax[Index]==Expected_MinMaxAvg[1].MaxValue);
	REQUIRE(abs(ConsoleOutputTemperatureMovingAvg[Index]-Expected_MinMaxAvg[1].MovingAvg)<0.1);
}
