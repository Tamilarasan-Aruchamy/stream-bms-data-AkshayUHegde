#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test/catch.hpp"
#include "SignalReceiver.h"
#include "BMS_ReceiverTestDoublesHeader.h"
#include<string.h>

extern int BSM_SignalReceiver();


TEST_CASE("Test the Number scanf function calls") 
{
	ResetTestInterface();
	
	char BSM_InputMessage[15][100]={"{\"charge_rate\": 18.69, \"temp_in_c\": 5.26}",\
                                    "{\"charge_rate\": 9.69, \"temp_in_c\": 6.26}",\
                                    "{\"charge_rate\": 10.69, \"temp_in_c\": 7.26}",\
                                    "{\"charge_rate\": 199.69, \"temp_in_c\": 8.26}",\
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
	REQUIRE(strcmp(ConsoleInputFormat[1],"%s")==0);
	REQUIRE(strcmp(ConsoleInputValue[1],BSM_InputMessage[1])==0);
	REQUIRE(printf_Func_CallCount==15);
	REQUIRE(ConsoleOutputTemperatureMin[3]==9.69f);
}

