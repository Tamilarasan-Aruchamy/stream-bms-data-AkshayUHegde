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
int delimitAndValidateMessage(char str[100],InputSignalConfig* BSM_Signals);
float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, float nextNum);
int delimit(char str[100],InputSignalConfig* BSM_Signals);
int delimitAndValidateSignals(char str[100],InputSignalConfig* BSM_Signals);
int IsValidSignalValue(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError);
int CountDots(char token,int *DotCounter);
int CountNonDigit(char token,int *NonDigitCounter);
int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError);

/*************************************************** function Definitions **************************************************/ 
int BSM_SignalReceiver()
{
	char BSM_InputMessageBuf[100];
                                    
	InputSignalConfig InputData[2]={{NULL,32767},{NULL,32767}};
	int FormatErrorDetected=1;
	MinMaxAvg ChargeRate={32767,-32767,0},Temp={32767,-32767,0};
    
	float MovAvg_ArrNumbers[2][5] = {0};   // Store the last 5 input records to MovingAvg.
	int pos = 0;
	float sum[2] = {0};
	int MovAvg_len=5;  // Number of last records to calculate MovingAvg.

	for(int i=0; i<15 ; i++)
		{	
		  scanf("%s",BSM_InputMessageBuf);  // Read from Console Buffer
		  FormatErrorDetected=delimitAndValidateMessage(BSM_InputMessageBuf,InputData);
		
		  if(!FormatErrorDetected)
			{
			  Calculate_MinMax(InputData[0].SignalValue, &ChargeRate); // Calculate Min & Max for ChargeRate Signal
                	  Calculate_MinMax(InputData[1].SignalValue, &Temp); // Calculate Min & Max for Temperature Signal
                
			  ChargeRate.MovingAvg = movingAvg(MovAvg_ArrNumbers[0], &sum[0], pos, MovAvg_len, InputData[0].SignalValue);  // Calculate MovAvg for ChargeRate Signal
			  Temp.MovingAvg = movingAvg(MovAvg_ArrNumbers[1], &sum[1], pos, MovAvg_len, InputData[1].SignalValue); // Calculate MovAvg for Temperature Signal
                
			  printf("ChargeRateMin:%0.2f ChargeRateMax:%0.2f ChargeRateAvg:%0.2f TempMin:%0.2f TempMax:%0.2f TempAvg:%0.2f\n", \
				 ChargeRate.MinValue,ChargeRate.MaxValue,ChargeRate.MovingAvg,Temp.MinValue,Temp.MaxValue,Temp.MovingAvg);
    		
			  pos++;
                   	  if (pos >= 5){
                    	  pos = 0;
                    	  }
            		}
		}
	
    	return 0;
}


int Calculate_MinMax(float SignalValue,MinMaxAvg *MinMax)  // Compare and retain the Min and Max vlaue of Input stream
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
	*ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;  	//Subtract the oldest number from the prev sum, add the new number
	ptrArrNumbers[pos] = nextNum;   			//Assign the nextNum to the position in the array
  	return *ptrSum / (float)len;    			//return the average
}



int delimitAndValidateMessage(char str[100],InputSignalConfig* BSM_Signals) 
{
	int FormatErrorDetected=0;
	
	if(str[0] != '{')			// Check the basic message format (e.g. {"charge_ratee": 1.69, "temp_in_c": 16.26} )
		{
       		  FormatErrorDetected=1;
   		}
   
   	else if(str[strlen(str)-1] != '}')      // Check the basic message format (e.g. {"charge_ratee": 1.69, "temp_in_c": 16.26} )
   		{
       		  FormatErrorDetected=1;
   		}
    
   	else
   		{
        	  FormatErrorDetected=delimitAndValidateSignals(str,BSM_Signals);  // Check the signal format.
   		}
   
   return FormatErrorDetected;
}


int delimitAndValidateSignals(char str[100],InputSignalConfig* BSM_Signals)
{
	const char s[6] = "{: ,}";
	char *token;
       	int FormatErrorDetected=0;
       	int cnt=0,NonDigitCounter=0,DotCounter=0;
           
	token = strtok(str, s);  // get the first token
        
        while( token != NULL ) 	// walk through other tokens
		{
		
         	  if(cnt<4){
        		  if(cnt%2){   
               			IsValidSignalValue(BSM_Signals, token, &cnt, &FormatErrorDetected);
            			}
        		  else{
				IsValidSignalName(BSM_Signals, token, &cnt, &FormatErrorDetected);
            			}
		           }
		
        	  else{
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
   
	for(int itr=0;itr<strlen(token);itr++){
    			CountDots(token[itr],&DotCounter);
    			CountNonDigit(token[itr],&NonDigitCounter);
			}
	
	if(DotCounter>1 || NonDigitCounter>0){ 		// check valid number  (e.g. 4.57 )
                    *FormatErrorDetected=1;
	           }
            
	else{  
		BSM_Signals[*cnt/2].SignalValue=atof(token);    // Conver "String" to "float" value if format is valid (e.g. "4.57" to 4.57f )
	    }
	
	return  0;
                
}

int CountDots(char token,int *DotCounter)  
{
	if(token=='.') 			// Count the Dot's in` Signal Value.(e.g, Input = 4.5.5 , "DotCounter" will be 2)
		{        
		  *DotCounter=*DotCounter+1;
		}
}


int CountNonDigit(char token,int *NonDigitCounter)  
{
	if((token < '0' || token > '9') && token!='.')  // Count the Non Digit letter in Signal Value except(Dot). (e.g, Input = 4.5e5 , "NonDigitCounter" will be 1)
        	{
                  *NonDigitCounter=*NonDigitCounter+1;
        	}
	return  0;
}



int IsValidSignalName(InputSignalConfig* BSM_Signals, char *token, int * cnt, int *InputMsgFormateError)
{
	if(strcmp(InputSignalName[*cnt/2],token))  //Check Input Signal name and format is Correct.
		{
		  *FormatErrorDetected=1;
                }            
        BSM_Signals[*cnt/2].SignalName=token;
                
        return  0;
}
