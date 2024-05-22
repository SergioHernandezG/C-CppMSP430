#include <msp430.h> 
#include <lcd.h>
#include <math.h>
#include <stdio.h>
void Numeros();
int unidades = 0, decenas = 0, millar = 0, centenas = 0, decimas = 0, centecimas = 0, milesimas = 0;
int cont=0,num=0,cont2=0;
float Val=0,Val1=0,Valor=0;
unsigned char columna=0, columna1=1,columna2=0,  columna4=8, columna3=7, columna6=6, columna5=5, fila=0;

int main(void){

// Inicio del main
                WDTCTL = WDTPW + WDTHOLD;
                P1OUT &= ~0xFF;                           // LIMPIA P1
                P2OUT &= ~0x3F;                           // LIMPIA P2
                P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
                P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
                ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
                ADC10CTL1 = INCH_7;                           // A1 COMO ENTRADA ANALOGICA
                ADC10AE0 |= 0x80;
                   Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
                   Conf_LCD1602();//configuracion de la pantalla LCD1602
               while(1)
                {
                ADC10CTL0 |= ENC + ADC10SC;                 // INICIO DE MUESTREO Y CONVERSION
                __bis_SR_register(CPUOFF + GIE);            // ENTRA AL MODO LPM0 PARA DEJAR SOLO AL ADC
                Numeros();
                }
}
void Numeros(){
   if(Valor >= 530)//466) //Valor es el sensado en bits que va de 0 a 1023
    {
       //3.6=1023.....3.3=937.75(valor maximo del sensor)...1.64=466.83(valorde origen)
       //937.75-466.83=470.92...... 180/469.67=0.382 (razon para obtener el valor real del voltaje sensado)
      //466.83 es la referencia en cero (1.64) ----0.385 es la razon para convertir a valor real ();
       Val=((Valor-510)*0.354);//466.83)*0.385);//convirtiendo el valor real
      if(Val>=0){//empieza las muestras de la paete positiva de la onda
          if(cont==1){
               num=num+1;     //conteo del numero de muestras por periodo
               Val1=Val1+Val*Val;// suma de cuadrados de los voltajes sensados durante de la parte positiva
         }
      }
    }
   if(Valor < 530)//466) //cuando cruza el cero y baja a la parte negativa
    {
      if(cont==1){//muestra el valor del vrms
                   if(Val1>0){
                    Val1=Val1/num; // las suma de los cuadrados sobre el numero de muestras
                     Val1=sqrt(Val1);// la raiza cuadrada de las suma de los cuadrados sobre el numero de muestras
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
                                                LCD1602_Printf("%i",&columna3,&fila,unidades);//muestra el vrms
                                                LCD1602_Printf("%i",&columna2,&fila,decenas);
                                                LCD1602_Printf("%i",&columna1,&fila,centenas);
                                                LCD1602_Printf(".%i",&columna4,&fila,centecimas);
                                                __delay_cycles(3000000);// detiene el cambio para poder apreciarlo en la LCD
                                                __delay_cycles(3000000);
                                                   unidades = 0; //reinicia los contadores
                                                   decenas = 0;
                                                   millar = 0;
                                                   centenas = 0;
                   cont=0;
                   cont2=0;
                   Val1=0;
                   num=0;
       }
      }
      if(cont==0){
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


