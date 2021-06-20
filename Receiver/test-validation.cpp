#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test/catch.hpp"
#include "SignalReceiver.h"
#include "BMS_ReceiverTestDoublesHeader.h"
#include <string.h>
#include <stdlib.h>

extern int BSM_SignalReceiver();


/*TEST_CASE("Test the Number scanf function calls") 
{
	ResetTestInterface();
	
	char BSM_InputMessage[15][100]={"{\"charge_rate\": 18.69, \"temp_in_c\": 5.26}",\
                                    "{\"charge_rate\": 9.69, \"temp_in_c\": 6.26}",\
                                    "{\"charge_rate\": 10.69, \"temp_in_c\": 7.26}",\
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
                                    "{\"charge_rate\": 22.69, \"temp_in_c\": 19.26}"};
	
	for(int i=0;i<15;i++)
	{
	strcpy(InputMessageBuf[i],BSM_InputMessage[i]);
	}
	
	REQUIRE(BSM_SignalReceiver()==1);
	REQUIRE(scanf_Func_CallCount==15);
}
*/
TEST_CASE("Test the Min Max and Avg") 
{
	ResetTestInterface();
	
	char BSM_InputMessage[15][100]={"{\"charge_rate\": 18.69, \"temp_in_c\": 5.26}",\
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
                                    "{\"charge_rate\": 22.69, \"temp_in_c\": 19.26}"};
	
	
	MinMaxAvg Expected_MinMaxAvg[15][2]={{{18.69,18.69,3.738000},{5.26,5.26,1.052000}},\
						{{9.69,18.69,5.676000},{5.26,6.26,2.304000}},\
					       {{9.69,18.69,7.814000},{5.26,21.26,6.556000}},\
					       {{9.69,30.69,13.952001},{5.26,21.26,8.208000}},\
					       {{9.69,30.69,16.490002},{5.26,21.26,10.060000}},\
					       {{9.69,30.69,15.490001},{5.26,21.26,11.060000}},\
					       {{9.69,30.69,16.490002},{5.26,21.26,12.060000}},\
					       {{9.69,30.69,17.490002},{5.26,21.26,10.060000}},\
					       {{9.69,30.69,14.690001},{5.26,21.26,11.060000}},\
					       {{9.69,30.69,15.690001},{5.26,21.26,12.060000}},\
					       {{9.69,30.69,15.690001},{5.26,21.26,13.0600000}},\
					       {{9.69,30.69,17.690001},{5.26,21.26,14.060000}},\
					       {{9.69,30.69,18.690001},{5.26,21.26,15.060000}},\
					       {{9.69,30.69,19.690001},{5.26,21.26,16.060000}},\
					       {{9.69,30.69,20.690001},{5.26,21.26,17.060000}}};
	
	for(int i=0;i<15;i++)
	{
	strcpy(InputMessageBuf[i],BSM_InputMessage[i]);
	}
	
	REQUIRE(BSM_SignalReceiver()==1);
	REQUIRE(scanf_Func_CallCount==15);
	
	REQUIRE(printf_Func_CallCount==15);
	
	for(int i=0;i<15;i++)
	{
	REQUIRE(strcmp(ConsoleInputFormat[i],"%s")==0);

	REQUIRE(ConsoleOutputTemperatureMin[i]==Expected_MinMaxAvg[i][0].MinValue);
	REQUIRE(ConsoleOutputTemperatureMax[i]==Expected_MinMaxAvg[i][0].MaxValue);
	REQUIRE(abs(ConsoleOutputTemperatureMovingAvg[i]-Expected_MinMaxAvg[i][0].MovingAvg)<0.1);
	
	REQUIRE(ConsoleOutputChargeRateMin[i]==Expected_MinMaxAvg[i][1].MinValue);
	REQUIRE(ConsoleOutputChargeRateMax[i]==Expected_MinMaxAvg[i][1].MaxValue);
	REQUIRE(abs(ConsoleOutputChargeRateMovingAvg[i]-Expected_MinMaxAvg[i][1].MovingAvg)<0.1);
	
		
			
	}
}
