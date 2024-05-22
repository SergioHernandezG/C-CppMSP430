#include <msp430.h> 
#include <lcd.h>
#include <math.h>
#include <stdio.h>
void Numeros();
int unidades = 0, decenas = 0, millar = 0, centenas = 0, decimas = 0, centecimas = 0, milesimas = 0;
int cont=0,num=1,cont2=5;
float Val=0,Val1=0,Valor=0;
unsigned char columna=0, columna1=1,columna2=0,  columna4=8, columna3=7, columna6=6, columna5=5, fila=0;

int main(void){

// Inicio del main
                WDTCTL = WDT_ADLY_16;                   // _1_9;SE CONFIGURA EL WDT PARA CONTAR 1000 ms
                IE1 = WDTIE;                              // SE HABILITA LA INTERRUPCION POR WDT
           ///  WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
                P1OUT &= ~0xFF;                           // LIMPIA P1
                P2OUT &= ~0x3F;                           // LIMPIA P2
                P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
                P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
                ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
                ADC10CTL1 = INCH_7;                           // A1 COMO ENTRADA ANALOGICA
                ADC10AE0 |= 0x80;
               // __bis_SR_register(GIE);
                   Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
                   Conf_LCD1602();//configuracion de la pantalla LCD1602
                   //LCD1602_Printf("-Sensor Vol-\n",&columna,&fila);
               while(1)
                {
                ADC10CTL0 |= ENC + ADC10SC;                 // INICIO DE MUESTREO Y CONVERSION
                __bis_SR_register(CPUOFF + GIE);            // ENTRA AL MODO LPM0 PARA DEJAR SOLO AL ADC
                //Val = ADC10MEM;
                Numeros();
                P2OUT &= ~0x03F;                           // P1.0-5  off
                columna1=1;
                columna2=2;
                columna3=3;
                columna4=4;
                columna5=5;
                columna6=6;
                LCD1602_Printf("%i",&columna3,&fila,unidades);
                LCD1602_Printf("%i",&columna2,&fila,decenas);
                LCD1602_Printf("%i",&columna1,&fila,centenas);
                LCD1602_Printf(".%i",&columna4,&fila,centecimas);
               // LCD1602_Printf("%i",&columna5,&fila,decimas);
              // Val1=0.0;
               // num=0;
               // LCD1602_Printf("%i",&columna6,&fila,milesimas);
                //__delay_cycles(1000);
            //    __low_power_mode_3(); // entramos en modo LPM3
                }
}
void Numeros(){
   unidades = 0;
   decenas = 0;
   millar = 0;
   centenas = 0;
   if(Valor >= 466.83) //466.033
    {
      //Val = (Val - 469)*0.3829;//*0.353; los 469 son del voltaje de referencia de la placa 1.65v y 0.3152 es 180/469.67 para obtener el valor real del voltaje sensado
      Val=((Valor-466.83)*0.385);//466.033  Y 0.3816
      if(cont==1){
               num=num+1;
               Val1=Val1+Val*Val;
      }

         }

  if(Valor < 466.33) //466.033
    {
      if(cont==1 && Val1>0){
                     Val1=num;
                     //Val1=sqrt(Val1);
                     if(Val1 >= 100)
                                     {
                                      while(Val1>=100)
                                      {
                                        Val1=Val1-100;
                                        centenas++;   //Obtenemos el valor de las centenas
                                       }       // min= centenas;
                                     }
                                  if(Val1 >= 10)
                                     {
                                      while(Val1>=10)
                                            {
                                               Val1=Val1-10;
                                               decenas++;   //Obtenemos el valor de las centenas
                                            }      //segundos = decenas;
                                     }
                                  if(Val1 >= 1)
                                     {
                                      while(Val1>=1)
                                            {
                                          Val1=Val1-1;
                                          unidades++;   //Obtenemos el valor de las centenas Val=Va
                                            }
                                     }
                                  if(Val1<1)
                                      {
                                      Val1=Val1*100;

                                      if(Val1 >= 10)
                                         {
                                          while(Val1>=10)
                                                {
                                              Val1=Val1-10;
                                              decimas++;   //Obtenemos el valor de las centenas Val=Va
                                                }
                                      }
                                      if(Val1 <= 9)
                                            {
                                                  centecimas=Val1;
                                            }
                                      }
                                                columna1=1;
                                                columna2=2;
                                                columna3=3;
                                                columna4=4;
                                                columna5=5;
                                                columna6=6;
                                                LCD1602_Printf("%i",&columna3,&fila,unidades);
                                                LCD1602_Printf("%i",&columna2,&fila,decenas);
                                                LCD1602_Printf("%i",&columna1,&fila,centenas);
                                                LCD1602_Printf(".%i",&columna4,&fila,centecimas);
          cont=0;
          Val1=0;
      }
      else{
      cont=1;
      }
    }

}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    Valor = ADC10MEM;
  __bic_SR_register_on_exit(CPUOFF);        // FORZA AL uC A SALIR DE LPM0
}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    LPM3_EXIT;                            // SALE DE LPM3
}
