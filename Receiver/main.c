/******************************************************* Header_Files *******************************************************/

#include "SignalProvider.h"

/********************************************** Function/Variable Declarations **********************************************/ 

extern int BSM_SignalProvider(OutputTarget OutputTargetIndex);

/*************************************************** function Definitions ***************************************************/ 

int main()
{
  BSM_SignalProvider(TO_CONSOLE);
  return 0;
}
