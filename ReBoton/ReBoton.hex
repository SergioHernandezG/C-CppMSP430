#include <msp430.h> 
void BCD();
void Segundero();
short  seg=0, segundos=0, min=0, minutos=0, hor=1, hora=0, num=0,display=0;
int cont=0;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Detiene el watchdog
  //P1DIR |= BIT0;            // P1.0 (LED) como salida digital
  BCSCTL1 |= DIVA_0;                        // ACLK /1
  BCSCTL3 |= LFXT1S_2;                      // SE CONFIGURA VLO
  CCR0 = 1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
  CCTL0 = CCIE;                             // INTERRUPCION EN MODO COMPARADOR
  TACTL = TASSEL_1|ID_0|MC_1;               // TACLK = TACLK, /1, Up mode, IE
  P1OUT &= ~0xFF;                           // LIMPIA P1
  P2OUT &= ~0x3F;                           // LIMPIA P2
  P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
  P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
  P1REN |= BIT7;        // Resistencia en P1.1 (pulsador derecho)
  P1OUT |= BIT7;        // Modo pull-up
  P1IE |= BIT7;         // habilita la interrupción de P1.1
  P1IES |= BIT7;        // Interrupción por flanco de bajada
  P1IFG &= ~(BIT7);     // baja flag de interrupción de P1.1

  // Activar interrupciones
  // también puede usarse: __enable_interrupt()
  __bis_SR_register(GIE);

  // bucle infinito.
  while (1) {
    __low_power_mode_3(); // entramos en modo LPM3
   // __no_operation();
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
}
/*void debounce(){
    WDTCTL = WDT_ADLY_1000;                   // SE CONFIGURA EL WDT PARA CONTAR  1000 ms
    IE1 = WDTIE;                              // SE HABILITA LA INTERRUPCION POR WDT

}*/
#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void) {
  if (P1IFG & BIT7) {   // comprobar fuente de la interrupción P1.1
    if (P1IN & BIT7) {  // Estado de P1.1: si está a 1 (no pulsado)
      Segundero();
     // P1OUT |= BIT0;    // Enciende LED
      P1IES |= BIT7;    // activación por flanco de bajada
    } else {            // y si no (pulsado),
      P1OUT &= ~BIT0;   // Apaga LED
      P1IES &= ~BIT7;   // activación por flanco de subida
    }
    P1IFG &= ~BIT7; // puesta a cero del flag de interrupción P1.1
   // Debounce();
  }
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    LPM0_EXIT;                            // SALE DE LPM3
    //display();
}
/*#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    LPM3_EXIT;
}*/
