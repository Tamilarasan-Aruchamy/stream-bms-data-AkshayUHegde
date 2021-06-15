#include <stdint.h>
#include <limits.h>
#define RAND_MAX INT_MAX

extern char* ConsoleOutputFormat[15];
extern float ConsoleOutputTemperature[15];
extern float ConsoleOutputSOC[15];
extern int printf_Func_CallCount;


extern int ResetTestInterface();
extern int rand();
extern int printf(char* Format, float Temperature, float SOC);


