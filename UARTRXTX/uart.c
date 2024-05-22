#include <msp430.h> 
// Este programa combina los led RGB encontrados en la launchpad
// con ayuda de la libreria UART; primero, se configura la UART;segundo,
// activamos la recepcion; tercero, leemos el dato de entrada; cuarto,
// lo transmitimos.
#include <UART.h>

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

char color;
int TABLABR0=1666;    // VALORES OBTENIDOS DE DATASHEET 9600 baudios
int TABLABR1=6,TABLAMCTL=12; // PARA RELOJ DE 16MHZ

int main(void)
{
   WDTCTL = WDTPW + WDTHOLD; // Stop WDT
   DCOCTL = 0; // Select lowest DCOx and MODx settings
   BCSCTL1 = CALBC1_16MHZ; // configuramos velocidad de reloj
   DCOCTL = CALDCO_16MHZ;
   P2DIR |= 0xFF; // All P2.x outputs
   P2OUT &= 0x00; // All P2.x reset
   P1SEL |= RXD + TXD ; // activamos funciones especiales
   P1SEL2 |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD
   P1DIR |= RXLED + TXLED;
   P1OUT &= 0x00;
   P1DIR =0x001;
   //-----------configuracion-----------
   CONFUART(TABLABR0,TABLABR1,TABLAMCTL);  //configuramos numero de baudios
   activacionRX();           //activamos RX
   color='c';
   setTX(color);
   while (1)
   {
       __bis_SR_register(CPUOFF + GIE); // modo bajo consumo
      color=getRX();            //obtine caracter
      switch(color){
      case 48: P1OUT =  0x001;          //rojo
      break;
      case 49: P1OUT &=  ~0x001;            //verde
      break;
      case 'b': P2OUT =  BIT5;            //azul
      break;
      case 'w': P2OUT =  BIT5+BIT3+BIT1;   //blanco
      break;
      case 'y': P2OUT =  BIT3+BIT1;      //amarillo
      break;
      case 'c': P2OUT =  BIT5+BIT3;     //cian
      break;
      case 'm': P2OUT =  BIT5+BIT1;     //magenta
      break;
      default : P2OUT= 0;
      }
      setTX(color);            //transmite caracter
   }
}
