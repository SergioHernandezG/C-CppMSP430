#include <msp430.h>
//----------------------VARIABLES------------------
static char dato;
char enviar;
//---------------------FUNCIONES-------------------------
void CONFUART(BR0,BR1,MCTL){
    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = BR0; // 9600
    UCA0BR1 = BR1; // 9600
    UCA0MCTL = MCTL;
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
}

void desActivacionRX(){
UC0IE |= ~UCA0RXIE; //desactiva interrupciones de rx
return;
}

void activacionRX(){
UC0IE |= UCA0RXIE; //activa interrupciones de rx
return;
}
//-----------OBTENER DATO-------------
char getRX(void){
    return dato;
}
//-----------ENVIAR DATO-----------
void setTX(char caracter){
       enviar=caracter;
       UC0IE |= UCA0TXIE; // activa interrupciones de tx
}

//--------------INTERRUPCIONES----------------------
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
     UCA0TXBUF = enviar; // asigna caracter al buffer para enviar
     UC0IE &= ~UCA0TXIE;  // Desactiva las interrupciones de tx

 }

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    dato= UCA0RXBUF; //lee el dato de entrada
    LPM0_EXIT;  // sale de LPM0 (OPCIONAL)
}
