
#include <xc.h>
#include "teclado.h"                /*llamamos a la libreria teclado*/
#include "lcd.h"                    /*llamamos a la libreria lcd*/
#include "config.h"
#include <stdlib.h>
#include <string.h>

void display_decimales(double);         /*imprimir los decimales de la division*/

int main() 
{
    
    unsigned int n_array=0;           /* variable para el array*/
    unsigned long num1,num2;  /*variable para almacenar los números*/
    unsigned long resultado=0;         /*variable de resultado de operación*/
    double div_res=0;            /*resutado de división*/
    unsigned char tecla,operador,flag=0;  /*tecla presionada,Operación '+','-' etc,
                                           varible que nos dira si se presiono un signo (+,-,*,/) para pasar al segundo número */
    unsigned char op1[10],op2[10];        
    unsigned char res_lcd[10];       /*variable de resultado que se va a ver en el LCD*/
    
    
    
    
    OSCCON = 0x72;
    RBPU=0;                             /* activar resistencias en pull-up */
    LCD_Init();                         /* inicializando LCD16x2 en modo 4bits */
    
    
    LCD_String_xy(1,0,"Calculadora");
    LCD_String_xy(2,0,"+,-,*,/");    
    MSdelay(1000);
    LCD_Clear();
    
    while(1){
      
        
      tecla= keyfind();                 /*usamos la funcion keyfind() para asignar la tecla que se presiono*/
      MSdelay(30);
      if(tecla!=' '){  
        
          
          
              if(tecla!='+' && tecla!='-' && tecla!='/' && tecla!='*' && tecla!='='){
                    
                    if(flag==0){
                        
                        op1[n_array] = tecla;       /*se asigna el primer numero al primer array */
                        n_array++;
                    }
                    else{
                        op2[n_array] = tecla;       /*se asigna el primer numero al primer array */
                        n_array++;
                    }    
                }
                      
                if(tecla=='+' || tecla=='-' || tecla=='*' || tecla=='/' ){
             
                    operador=tecla;              /*guardamos el operador*/
                     n_array=0;                  /*reiniciamos la variable para el segundo arreglo*/
                     flag=1;                        
                     
                }
                
                
                if(tecla=='='){ 
                
                  num1=atol(op1);                   /*convertimos el arreglo a un número*/
                  num2=atol(op2);                   /*convertimos el arreglo a un número*/
                 LCD_Command(0xc0);               /*cambiamos a la segunda linea del lcd*/
                
                     
                    switch(operador){
                        /*Caso sea suma*/
                        case '+':                       


                                    resultado = num1+num2;
                                    ltoa(res_lcd,resultado,10); /*convierte de número a string para imprimirlo en el LCD*/
                                    LCD_String(res_lcd);
                                    break;

                        /*Caso resta*/            
                        case '-':

                                    resultado = num1-num2;
                                    ltoa(res_lcd,resultado,10);
                                    LCD_String(res_lcd);
                                    break;

                        /*Caso multiplicación*/
                        case '*':

                                    resultado = num1*num2;
                                    ltoa(res_lcd,resultado,10);
                                    LCD_String(res_lcd);
                                    break;

                        /*Caso división*/
                        case '/':

                                    if(num2==0){  /*matematicamente división no definisa*/

                                        LCD_Clear();
                                        LCD_String("ERROR");
                                    }
                                    else{   

                                        div_res = (float)num1/(float)num2;     /*resultado de la division de los 2 números */

                                         /*función para imprimir decimales en LCD*/
                                        display_decimales(div_res);

                                    }   
                                    break;

                        default :

                            break;
                    }        
                
          }
            
    
        }
        else{
          
          LCD_Clear();                    //borramos el display  
          MSdelay(10);
          
          memset(op1,0,10);             /*borramos con la funcion memset el arreglo 1 */
          memset(op2,0,10);             /*borramos el arreglo 2*/    
          memset(res_lcd,0,10);          /*borramos el arreglo del resultado final*/
          break;
        }    
      
        MSdelay(1);
    }
    return 0;
}

void display_decimales(double div_res)
{
    float temp;
    unsigned char salida[15],salida1[15];
        itoa(salida,(int)div_res,10);        /*convetimos la parte entera en strind*/
        LCD_String(salida);                      /*imprimimos la parte real*/
        LCD_String(".");                         /*imprimimos el punto decimal*/
            
        temp=div_res - ((int)div_res);    /* almacenamos la parte decimal en la variable temp*/
        temp=10*temp;                          /*pasamos el primer decimal a las unidades*/
        itoa(salida1,(int)temp,10);             /*convertimos el primer decimal en string*/
        LCD_String(salida1);                    /*imprimimos el primer decimal*/
        
         /*y se repite los paso anteriores para imprimir los demas decimales*/
        
        temp= temp - ((int)temp);    
        temp=10*temp;
        itoa(salida1,(int)temp,10);             
        LCD_String(salida1);
        
        temp= temp - ((int)temp);    
        temp=10*temp;
        itoa(salida1,(int)temp,10);             
        LCD_String(salida1);
        
        temp= temp - ((int)temp);    
        temp=10*temp;
        itoa(salida1,(int)temp,10);            
        LCD_String(salida1);
        
        temp= temp - ((int)temp);    
        temp=10*temp;
        itoa(salida1,(int)temp,10);             
        LCD_String(salida1);
}
