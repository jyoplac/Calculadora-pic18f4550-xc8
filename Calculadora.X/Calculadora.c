
#include <xc.h>
#include "teclado.h"
#include "lcd.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

void display_float(double);         /*convert float value to string*/

int main() 
{
    
    unsigned int index=0;           /*Define variable for indexing of array*/
    unsigned long number1,number2;  /*Define variable for storing no.*/
    unsigned long result=0;         /*To store Result of operation*/
    double div_result=0;            /*Store division float result*/
    unsigned char key_pressed,operator,flag=0;  /*key for key pressed,Operator for '+','-' etc*/
    unsigned char op1[10],op2[10];        
    unsigned char result_output[10];       /*variable for Displaying result on LCD*/
    
    
    
    
    OSCCON = 0x72;
    RBPU=0;                             /* activate pull-up resistor */
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    
    
    LCD_String_xy(1,0,"Calculadora");
    LCD_String_xy(2,0,"+,-,*,/");    
    MSdelay(1000);
    LCD_Clear();
    LCD_Command(0x80);                  /* display pressed key on 2nd line of LCD */
    while(1){
      
        
      key_pressed= keyfind();                       /*Call keyfind() function for detecting pressed key*/
      MSdelay(30);
      if(key_pressed!=' '){  
        
          
          
              if(key_pressed!='+' && key_pressed!='-' && key_pressed!='/' && key_pressed!='*' && key_pressed!='='){
                    
                    if(flag==0){
                        
                        op1[index] = key_pressed;       /*Assign 1st no string to op1 stored that in array*/
                        index++;
                    }
                    else{
                        op2[index] = key_pressed;       /*Assign 2nd no string to op2 stored that in array*/
                        index++;
                    }    
                }
                      
                if(key_pressed=='+' || key_pressed=='-' || key_pressed=='*' || key_pressed=='/' ){
             
                    operator=key_pressed;              /*Store operator*/
                     index=0;                       /*For another value enter of 2nd no.*/
                     flag=1;                        
                     
                }
                
                
                if(key_pressed=='='){ 
                
                  number1=atol(op1);                   /*C function(<stdlib.h>) used to convert string into long integer*/
                  number2=atol(op2);                   /*C function(<stdlib.h>) used to convert string into long integer*/
                 LCD_Command(0xc0);               /*Start displaying result on 2nd Row and 1st location*/
                
                     
                    switch(operator){
                        /*Case for addition operation*/
                        case '+':                       


                                    result = number1+number2;
                                    ltoa(result_output,result,10); /*C function(<stdlib.h>) 
                                                             convert long integer value to string for display*/
                                    LCD_String(result_output);
                                    break;

                        /*Case for Subtraction operation*/            
                        case '-':

                                    result = number1-number2;
                                    ltoa(result_output,result,10);
                                    LCD_String(result_output);
                                    break;

                        /*Case for Multiplication operation*/
                        case '*':

                                    result = number1*number2;
                                    ltoa(result_output,result,10);
                                    LCD_String(result_output);
                                    break;

                        /*Case for Division operation*/
                        case '/':

                                    if(number2==0){  /*Check for math error*/

                                        LCD_Clear();
                                        LCD_String("ERROR");
                                    }
                                    else{   

                                        div_result = (float)number1/(float)number2;     /*result should be in float */

                                         /*Function used display float value*/
                                        display_float(div_result);

                                    }   
                                    break;

                        default :

                            break;
                    }        
                
                    
                    
                 
          }
            
    
        }
        else{
          
          LCD_Clear();                    //Clear display screen    
          MSdelay(10);
          
          memset(op1,0,10);             //memset Clear array of no.1 by copying 0 to op1's 10 location*/
          memset(op2,0,10);             //Clear array of no.2*/    
          memset(result_output,0,10);          //Clear array of output array which display final result*/
          break;
        }    
      
        MSdelay(1);
    }
    return 0;
}

void display_float(double div_result)
{
    float temp;
    unsigned char output[15],output1[15];
        temp=div_result - ((int)div_result);    /* get value after decimal point i.e. float value*/
        temp=10*temp;                          /*convert it into non-decimal value*/
        itoa(output,(int)div_result,10);        /*convert value before deciaml point into ASCII value*/
        LCD_String(output);                      
        LCD_String(".");                         /*Display Decimal point*/
        itoa(output1,(int)temp,10);             /*convert value after deciaml point into ASCII value*/
        LCD_String(output1);
        
        temp= temp - ((int)temp);    /* get value after decimal point i.e. float value*/
        temp=10*temp;
        itoa(output1,(int)temp,10);             /*convert value after deciaml point into ASCII value*/
        LCD_String(output1);
        
        temp= temp - ((int)temp);    /* get value after decimal point i.e. float value*/
        temp=10*temp;
        itoa(output1,(int)temp,10);             /*convert value after deciaml point into ASCII value*/
        LCD_String(output1);
        
        temp= temp - ((int)temp);    /* get value after decimal point i.e. float value*/
        temp=10*temp;
        itoa(output1,(int)temp,10);             /*convert value after deciaml point into ASCII value*/
        LCD_String(output1);
        
        temp= temp - ((int)temp);    /* get value after decimal point i.e. float value*/
        temp=10*temp;
        itoa(output1,(int)temp,10);             /*convert value after deciaml point into ASCII value*/
        LCD_String(output1);
}
