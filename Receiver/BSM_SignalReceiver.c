/******************************************************* Header_Files *******************************************************/ 

#include "SignalReceiver.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


/********************************************** Function/Variable Declarations **********************************************/ 

static char InputSignalName[2][15]={"\"charge_rate\"","\"temp_in_c\""};

int Calculate_MinMax(float SignalValue,MinMaxAvg *MinMax);
int Claculate_MovingAvg(float SignalValue,MinMaxAvg *Avg);
int delimit(char str[100],InputSignalConfig* BSM_Signals);
int Split(char str[100],InputSignalConfig* BSM_Signals);
int IsValidSignalValue(InputSignalConfig* BSM_Signals, char *token, int * cnt);
void CountDots(char *token,int *DotCounter);
void CountNonDigit(char *token,int *NonDigitCounter);
int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt);

/*************************************************** function Definitions **************************************************/ 
int BSM_SignalReceiver()
{
   char BSM_InputMessage[15][100]={"{\"charge_rate\": 8.69, \"temp_in_c\": 5.26}",\
                                    "{\"charge_rate\": 9.69, \"temp_in_c\": 6.26}",\
                                    "{\"charge_rate\": 10.69, \"temp_in_c\": 7.26}",\
                                    "{\"charge_rate\": 11.69, \"temp_in_c\": 8.26}",\
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
                                    
    InputSignalConfig InputData[2]={{NULL,32767},{NULL,32767}};
    int returnval;
    MinMaxAvg Temp={32767,-32767,0},ChargeRate={32767,-32767,0};

    for(int i=0; i<15 ; i++)
	{
		
	//	scanf("%s",BSM_InputMessage);
		returnval=delimit(BSM_InputMessage[i],InputData);
		
		if(returnval)
		    {
		        printf("InputMessage Invalid or InputMessage Formate Error\n");
		    }

        else
            {
                printf("%s\n", InputData[0].SignalName);
                printf("%f\n", InputData[0].SignalValue);
                printf("%s\n", InputData[1].SignalName);
                printf("%f\n", InputData[1].SignalValue);
                
                Calculate_MinMax(InputData[0].SignalValue, &Temp);
                Calculate_MinMax(InputData[1].SignalValue, &ChargeRate);
                Claculate_MovingAvg(InputData[0].SignalValue, &Temp);
                Claculate_MovingAvg(InputData[1].SignalValue, &ChargeRate);
               
               printf("Min:%f Max:%f\n", Temp.MinValue,Temp.MaxValue);
               printf("Min:%f Max:%f\n", ChargeRate.MinValue,ChargeRate.MaxValue);
               
            }
	}
    
    
    
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


int Claculate_MovingAvg(float SignalValue,MinMaxAvg *Avg)
{
    
}

int delimit(char str[100],InputSignalConfig* BSM_Signals) {
   //char str[190] = "{\"charge_rate\": 8.69, \"temp_in_c\": 5.26}";

   
   bool InputMsgFormateError=false;

   if(str[0] != '{')
   {
       InputMsgFormateError=true;
   }
   
   else if(str[strlen(str)-1] != '}')
   {
       InputMsgFormateError=true;
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
       bool InputMsgFormateError=false;
       int cnt=0,NonDigitCounter=0,DotCounter=0;
           /* get the first token */
        token = strtok(str, s);

        /* walk through other tokens */
        while( token != NULL ) {
         
        if(cnt<4)
        {
        if(cnt%2)
            {   
                InputMsgFormateError=IsValidSignalValue(BSM_Signals, token, &cnt);
            
            }
        else
            {

                InputMsgFormateError=IsValidSignalName(BSM_Signals, token, &cnt);
            }

        }
        else 
        {
            InputMsgFormateError=true;

        }
         cnt++;
         
         
        token = strtok(NULL, s);
   }
   return InputMsgFormateError;
}

int IsValidSignalValue(InputSignalConfig* BSM_Signals, char *token, int * cnt)
{
    int NonDigitCounter=0,DotCounter=0;
    
       bool InputMsgFormateError=false;
    

    CountDots(token,&DotCounter);
    CountNonDigit(token,&NonDigitCounter);
    
                
             if(DotCounter>1 || NonDigitCounter>0)
                {
                    InputMsgFormateError=true;

                }
            
              else
                {  
                    BSM_Signals[*cnt/2].SignalValue=atof(token);
                }
           return  InputMsgFormateError;
                
}

void CountDots(char *token,int *DotCounter)
{
         for(int itr=0;itr<strlen(token);itr++)
                {   
                    if(token[itr]=='.')
                    {
                        *DotCounter++;
                    }
                }
}

void CountNonDigit(char *token,int *NonDigitCounter)
{
         for(int itr=0;itr<strlen(token);itr++)
                {   
                    if(token[itr] < '0' || token[itr] > '9')
                    {
                        *NonDigitCounter++;
                    }
                }
}




int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt)
{
       bool InputMsgFormateError=false;
    
            if(strcmp(InputSignalName[*cnt/2],token))
                {
                   InputMsgFormateError=true;
                }
                
                BSM_Signals[*cnt/2].SignalName=token;
                
            return  InputMsgFormateError;
}
