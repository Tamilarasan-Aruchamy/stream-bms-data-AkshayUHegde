extern char InputMessageBuf[15][100];
extern char ConsoleScanfFormat[15][15];
extern char ConsolePrintfFormat[15][200];
extern float	ConsoleOutputChargeRateMin[15];
extern float	ConsoleOutputChargeRateMax[15];
extern float	ConsoleOutputChargeRateMovingAvg[15];
extern float	ConsoleOutputTemperatureMin[15];
extern float	ConsoleOutputTemperatureMax[15];
extern float	ConsoleOutputTemperatureMovingAvg[15];
extern int printf_Func_CallCount;
extern int scanf_Func_CallCount;


extern int ResetTestInterface();
extern int scanf(char *format, char * InputBuffer);
extern int printf(char *format, float ChargeRate_MinValue, float ChargeRate_MaxValue, float ChargeRate_MovingAvg, float Temp_MinValue, float Temp_MaxValue, float Temp_MovingAvg);
