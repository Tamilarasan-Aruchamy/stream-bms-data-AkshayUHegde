/******************************************************* Header_Files *******************************************************/ 

#include "SignalReceiver.h"
#include <string.h>
#include <stdlib.h>

#ifdef UNIT_TEST   	// include when building the Test code
	#include "BMS_ReceiverTestDoublesHeader.h"   
#else			// include when building the Production code
	#include <stdio.h>
#endif

/********************************************** Function/Variable Declarations **********************************************/ 

static char InputSignalName[2][15]={"\"charge_rate\"","\"temp_in_c\""};
int BSM_SignalReceiver();
int Calculate_MinMax(float SignalValue,MinMaxAvg *MinMax);
int delimit(char str[100],InputSignalConfig* BSM_Signals);
float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, float nextNum);
int delimit(char str[100],InputSignalConfig* BSM_Signals);
int Split(char str[100],InputSignalConfig* BSM_Signals);
int IsValidSignalValue(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError);
void CountDots(char token,int *DotCounter);
void CountNonDigit(char token,int *NonDigitCounter);
int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError);

/*************************************************** function Definitions **************************************************/ 
int BSM_SignalReceiver()
{
    char BSM_InputMessage[100];
                                    
    InputSignalConfig InputData[2]={{NULL,32767},{NULL,32767}};
    int returnval,mainreturnval=0;
    MinMaxAvg Temp={32767,-32767,0},ChargeRate={32767,-32767,0};
    
    float arrNumbers[2][5] = {0};

  int pos = 0;
  float sum[2] = {0};
  int len=5;

    for(int i=0; i<15 ; i++)
	{
		
		scanf("%s",BSM_InputMessage);
		returnval=delimit(BSM_InputMessage,InputData);
		
		if(!returnval)
		{
                Calculate_MinMax(InputData[0].SignalValue, &Temp);
                Calculate_MinMax(InputData[1].SignalValue, &ChargeRate);

                Temp.MovingAvg = movingAvg(arrNumbers[0], &sum[0], pos, len, InputData[0].SignalValue);
                ChargeRate.MovingAvg = movingAvg(arrNumbers[1], &sum[1], pos, len, InputData[1].SignalValue);
                pos++;
                if (pos >= 5){
                    pos = 0;
                    }
               
               
              printf("TempMin:%f TempMax:%f TempAvg:%f ChargeRateMin:%f ChargeRateMax:%f ChargeRateAvg:%f\n", Temp.MinValue,Temp.MaxValue,Temp.MovingAvg,ChargeRate.MinValue,ChargeRate.MaxValue,ChargeRate.MovingAvg);
               mainreturnval=1;
            }
	}
    
    return mainreturnval;
}

int Calculate_MinMax(float SignalValue,MinMaxAvg *MinMax)
{
    if(MinMax->MinValue>SignalValue)
        {
            MinMax->MinValue=SignalValue;
        }
    if(MinMax->MaxValue<SignalValue)
        {
            MinMax->MaxValue=SignalValue;
        }

}



float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, float nextNum)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
  //Assign the nextNum to the position in the array
  ptrArrNumbers[pos] = nextNum;
  //return the average
  return *ptrSum / (float)len;
}


int delimit(char str[100],InputSignalConfig* BSM_Signals) {
   //char str[190] = "{\"charge_rate\": 8.69, \"temp_in_c\": 5.26}";

   
   int InputMsgFormateError=0;

   if(str[0] != '{')
   {
       InputMsgFormateError=1;
   }
   
   else if(str[strlen(str)-1] != '}')
   {
       InputMsgFormateError=1;
   }
    
   else
   {
        InputMsgFormateError=Split(str,BSM_Signals);
   }
   
   return InputMsgFormateError;
}

int Split(char str[100],InputSignalConfig* BSM_Signals)
{
       const char s[6] = "{: ,}";
       char *token;
       int InputMsgFormateError=0;
       int cnt=0,NonDigitCounter=0,DotCounter=0;
           /* get the first token */
        token = strtok(str, s);

        /* walk through other tokens */
        while( token != NULL ) {
         
        if(cnt<4)
        {
        if(cnt%2)
            {   
               IsValidSignalValue(BSM_Signals, token, &cnt, &InputMsgFormateError);
            
            }
        else
            {

                IsValidSignalName(BSM_Signals, token, &cnt, &InputMsgFormateError);
            }

        }
        else 
        {
            InputMsgFormateError=1;

        }
         cnt++;

        token = strtok(NULL, s);
   }
   return InputMsgFormateError;
}

int IsValidSignalValue(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError)
{
    int NonDigitCounter=0,DotCounter=0;

    
for(int itr=0;itr<strlen(token);itr++)
{
    CountDots(token[itr],&DotCounter);
    CountNonDigit(token[itr],&NonDigitCounter);
}
                if(DotCounter>1 || NonDigitCounter>0)
                { 
                    *InputMsgFormateError=1;

                }
            
              else
                {  
                    BSM_Signals[*cnt/2].SignalValue=atof(token);
                }
           return  0;
                
}

void CountDots(char token,int *DotCounter)
{
                    if(token=='.')
                    {
                        
                        *DotCounter=*DotCounter+1;
                    }
}

void CountNonDigit(char token,int *NonDigitCounter)
{
  
                    if((token < '0' || token > '9') && token!='.')
                    {
                        *NonDigitCounter=*NonDigitCounter+1;

                    }

}


int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError)
{
      
    
            if(strcmp(InputSignalName[*cnt/2],token))
                {
                   *InputMsgFormateError=1;
                }
                
                BSM_Signals[*cnt/2].SignalName=token;
                
            return  0;
}
