#include <msp430.h>  
void BCD();
void Numeros();
short   num=0, seg=0, segundos=0, min=0, minutos=0, display=0;
//int const hor=1, hora=0;
int unidades = 0, decenas = 0, millar = 0, centenas = 0;
int cont=0,Val=0;


int main(void)

{// Inicio del main
    
                WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
                P1OUT &= ~0xFF;                           // LIMPIA P1
                P2OUT &= ~0x3F;                           // LIMPIA P2
                P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
                P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
                ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
                ADC10CTL1 = INCH_7;                           // A1 COMO ENTRADA ANALOGICA
                ADC10AE0 |= 0x80;
                

               while(1)  
                   
                {
                //ADC10CTL0 |= ENC + ADC10SC;  //muestreo pot
                //Val = ADC10MEM & 0xBB8;
                ADC10CTL0 |= ENC + ADC10SC;                 // INICIO DE MUESTREO Y CONVERSION
                __bis_SR_register(CPUOFF + GIE);            // ENTRA AL MODO LPM0 PARA DEJAR SOLO AL ADC
                //Val = ADC10MEM;
                Numeros();
                P2OUT &= ~0x03F;                           // P1.0-5  off
                
                
                switch (display)
                          
                     {
                                case 0: display ++;
                                            cont++;
                                            num = seg;
                                            BCD();
                                            P2OUT = 0x01;
                                            break;
                                case 1: display ++;
                                            cont++;
                                            num = segundos;
                                            BCD();
                                            P2OUT = BIT1;
                                            break;
                                case 2: display ++;
                                            cont++;
                                            num = min;
                                            BCD();
                                            P2OUT =BIT2 ;
                                            break;
                                 default: display=0;
                                            cont++;
                                            num = minutos;
                                            BCD();
                                            P2OUT = BIT3;
                                         // disp = -1;
                                            break;
                    }
                
                } //Terminación del while
}


void Numeros(){

    //Val2 = Val;
   unidades = 0;
   decenas = 0;
   millar = 0;
   centenas = 0;


    if(Val >= 1000)
       {
       while(Val>=1000)
        {
          Val=Val-1000;
          millar++;   //Obtenemos el valor de las unidades de millar
        }
        minutos = millar;

       }


    if(Val >= 100)
       {
        while(Val>=100)
        {
          Val=Val-100;
          centenas++;   //Obtenemos el valor de las centenas
         }
         min= centenas;

       }


    if(Val >= 10)
       {
        while(Val>=10)
              {
                 Val=Val-10;
                 decenas++;   //Obtenemos el valor de las centenas
              }
        segundos = decenas;

       }

    if(Val <= 9)
       {
        unidades=Val;
        seg =unidades ;

       }


    minutos = millar;
    min= centenas;
    segundos = decenas;
    seg = unidades;
 return;

}
void BCD(){
  switch (num)
        {
        case 0: P1OUT = 0x07E;
                break;
        case 1: P1OUT = 0x030;
                break;
        case 2: P1OUT = 0x06D;
                break;
        case 3: P1OUT = 0x079;
                break;
        case 4: P1OUT = 0x033;
                break;
        case 5: P1OUT = 0x05B;
                break;
        case 6: P1OUT = 0x01F;
                break;
        case 7: P1OUT = 0x071;
                break;
        case 8: P1OUT = 0x07F;
                break;
        default:P1OUT = 0x073;
                break;
    }
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    Val = ADC10MEM;
  __bic_SR_register_on_exit(CPUOFF);        // FORZA AL uC A SALIR DE LPM0
}

