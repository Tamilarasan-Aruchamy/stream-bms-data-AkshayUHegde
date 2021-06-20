extern char InputMessageBuf[15][100];
extern char* ConsoleInputFormat[5];
extern char* ConsoleOutputFormat[15];
extern float	ConsoleOutputTemperatureMin[15];
extern float	ConsoleOutputTemperatureMax[15];
extern float	ConsoleOutputTemperatureMovingAvg[15];
extern float	ConsoleOutputChargeRateMin[15];
extern float	ConsoleOutputChargeRateMax[15];
extern float	ConsoleOutputChargeRateMovingAvg[15];
extern int printf_Func_CallCount;
extern int scanf_Func_CallCount;


extern int ResetTestInterface();
extern int scanf(char *format, char * InputBuffer);
extern int printf(char *format, float Temp_MinValue, float Temp_MaxValue, float Temp_MovingAvg, float ChargeRate_MinValue, float ChargeRate_MaxValue, float ChargeRate_MovingAvg);
