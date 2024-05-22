#include <msp430.h> 
char dato,color;
int main(void)
{
     WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
     P1SEL |= BIT6 + BIT7;
     P1SEL2 |= BIT6 + BIT7;
     P1OUT &= ~0x001;                           // LIMPIA P1
     //P2OUT &= ~0x3F;                           // LIMPIA P2
     P1DIR = 0x001;                             // P1.0-P1.6 COMO SALIDA
     //P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
     UCB0CTL1 |= UCSWRST;
     UCB0CTL0 = UCMODE_3 | UCSYNC;//I2C esclavo
     UCB0I2COA = 0x48;
     UCB0CTL1 &= ~UCSWRST;
     UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
     IE2 |= UCB0TXIE;                          // Enable TX interrupt
     while (1)
     {
      //   PTxData = (unsigned char *)TxData;      // Start of TX buffer
        //     TXByteCtr = 0;                          // Clear TX byte coun
       __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                               // Remain in LPM0 until master
                                               // finishes RX
       __no_operation();                       // Set breakpoint >>here<< and
     }                                         // read out the TXByteCtr counter
   //  i2c_confi();
     //UC0IE = UCA0RXIE;// interrupciones por recepcion

     while (1)
        {
            __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
           color=dato;            //obtine caracter
           switch(color){
           case 'a': P1OUT =  0x01;//encendido
           break;
           case 'b': P1OUT &=  ~0x01;//apagado
           break;
           default : P1OUT = 0x01;
           }
           //setTX(color);            //transmite caracter
        }
}



#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    dato= UCB0RXBUF; //lee el dato de entrada
    switch(dato){
               case 0x001: P1OUT =  0x01;//encendido
               break;
               case 0x002: P1OUT &=  ~0x01;//apagado
               break;
               default : P1OUT &=~0x01;//apagado
               }
   // P1OUT =  0x01;
    LPM0_EXIT;  // sale de LPM0 (OPCIONAL)
}
