#include <msp430.h> 
void BCD();
void Segundero();
short  seg=0, segundos=0, min=0, minutos=0, hor=1, hora=0, num=0,display=0;
int cont=0;
int main(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
    //WDTCTL = WDT_ADLY_1000;                   // SE CONFIGURA EL WDT PARA CONTAR  1000 ms
      //  IE1 = WDTIE;                              // SE HABILITA LA INTERRUPCION POR WDT
        BCSCTL1 |= DIVA_0;                        // ACLK /1
        BCSCTL3 |= LFXT1S_2;                      // SE CONFIGURA VLO
        CCR0 = 1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
        CCTL0 = CCIE;                             // INTERRUPCION EN MODO COMPARADOR
        TACTL = TASSEL_1|ID_0|MC_1;               // TACLK = TACLK, /1, Up mode, IE
        P1OUT &= ~0xFF;                           // LIMPIA P1
        P2OUT &= ~0x3F;                           // LIMPIA P2
        P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
        P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
       /*P1REN |= 0x80;                            // HABILITA PULLUP/PULLDOWN EN P1.7
        P1OUT |= 0x80;                            // PULLUP
        P1IE |= 0x80;                             // SE HABILITA LA INTERRUPCION EN EL PUERTO 1
        P1IES |= 0x80;                            // HIGH TO LOW TRANSITION
        P1IFG &= ~0x80;                           // SE LIMPIA LA BANDERA DE INTERRUPCION
*/
// __bis_SR_register(LPM3_bits + GIE);       // LPM0+INTERRUPCION

        while(1)
        {
           // ADC10CTL0 |= ENC + ADC10SC;                 // INICIO DE MUESTREO Y CONVERSION
               // __bis_SR_register(CPUOFF + GIE);            // ENTRA AL MODO LPM0 PARA DEJAR SOLO AL ADC
                __bis_SR_register(LPM0_bits + GIE);       // LPM0+INTERRUPCION
                P2OUT &= ~0x03F;                           // P1.0-5  off
                // cont++;
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
                        case 3: display ++;
                                cont++;
                                num = minutos;
                                BCD();
                                P2OUT = BIT3;
                                break;
                        case 4: display ++;
                                cont++;
                                num = hor;
                                BCD();
                                P2OUT = BIT4;
                                break;
                        default: display=0;
                                cont++;
                                num = hora;
                                BCD();
                                P2OUT = BIT5;
                               // disp = -1;
                                break;
                    }
                if(cont==0x179A){
                   Segundero();
                }
        }
}
void Segundero(){
    cont=0;
    seg++;
    if(seg==10){
         seg=0;
         segundos++;
         if(segundos==6){
             segundos=0;
             min++;
             if(min==10){
                 min=0;
                 minutos++;
                 if(minutos==6){
                     minutos=0;
                     hor++;
                     if(hora==1){
                         if(hor==3){
                             hor=0;
                             hora=0;
                         }
                     }
                     if(hor==10){
                              hor=0;
                              hora++;
                     }
                 }
             }
         }
       }
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
}//-------------------------interrupciones

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    LPM0_EXIT;                            // SALE DE LPM3
    //display();
}
