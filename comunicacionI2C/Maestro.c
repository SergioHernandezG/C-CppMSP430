#include <msp430.h> 
int main(void)
{
     WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
     // Both UART & I2C
     P1SEL = BIT6 + BIT7;        // UART: P1.1 = RXD, P1.2=TXD
                                                // & i2C: P1.6 = data line, P1.7 = clock
     P1SEL2 = BIT6 + BIT7;       // UART: P1.1 = RXD, P1.2=TXD
     UCB0CTL1 |= UCSWRST;                      //Activar SW reset
     UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
     UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
     UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
     UCB0BR1 = 0;
     UCB0I2CSA = 0x48;                         // Slave Address initialization
     UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
     while (1){
     UCB0CTL1 |= UCTR | UCTXSTT; //PARA INICIAR

     while(UCB0CTL1 & UCTXSTT){
         UCB0TXBUF = 0x0001; //01=encendido, 11=apagado
        // UCB0CTL1 |= UCTXSTT
     }
     }

     }
