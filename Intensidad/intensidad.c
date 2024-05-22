#include <msp430.h> 


int cont=0,WDT_dcnt=0,Debounce=1;
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
  //  WDTCTL = WDT_ADLY_1_9;                   // SE CONFIGURA EL WDT PARA CONTAR 1000 ms
  //  IE1 = WDTIE;                              // SE HABILITA LA INTERRUPCION POR WDT
    CCR0 =1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
    CCTL0 = CCIE;                           // INTERRUPCION EN MODO COMPARADOR
    TACTL = TASSEL_1|ID_0|MC_1;               // TACLK = TACLK, /1, Up mode, IE

    P1OUT &= ~0x01;                           // LIMPIA P2
    P1DIR = 0x01;
    P1REN |= BIT7;        // Resistencia en P1.7 (pulsador derecho)
    P1OUT |= BIT7;        // Modo pull-up
    P1IE |= BIT7;         // habilita la interrupción de P1.7
    P1IES |= BIT7;        // Interrupción por flanco de bajada
    P1IFG &= ~(BIT7);     // baja flag de interrupción de P1.7
    __bis_SR_register(GIE);
    while (1) {
     //  cont++;


          __low_power_mode_3(); // entramos en modo LPM3
     }
//	return 0;
}
/*------------------funcion----------------*/
void Configuracion(){
    WDT_dcnt=0;
    __delay_cycles(1000000);
    P1OUT = 0x01;
}
/*--------------------------------vectores de interrupcion-----------*/
#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void) {
    P1IFG &= ~BIT7; // puesta a cero del flag de interrupción P1.7
    WDT_dcnt=Debounce;//manda un pulso a al WDT para decirle que se pulso el boton

}
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    LPM3_EXIT;                            // SALE DE LPM3
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    if(WDT_dcnt>0){ // verifica si se a pulsado el boton
        __delay_cycles(100000);
        P1OUT &= ~0x01;    // modifica la hora deacuerdo a la opcion donde se encuentre
        }
    else{// verifica si el boton sigue pulsado
        Configuracion();    //     Tiempo(); //si, mada a llamar a la funcion tiempo para hacer el conteo del tiempo del pulso
            }
}
