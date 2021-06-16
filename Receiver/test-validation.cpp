#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test/catch.hpp"
#include "SignalReceiver.h"
#include "BMS_ReceiverTestDoublesHeader.h"
#include<stddef.h>
#include<string.h>

extern int BSM_SignalReceiver();


TEST_CASE("Test the Number scanf function calls") 
{
	BSM_SignalReceiver();
}

