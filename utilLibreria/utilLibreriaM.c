#include <msp430.h> 
#include <motor.h>
//int Grados=10;                    //por cada giro da 36 grados
int main(void)
{
        WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
        Giros(-10);
        Giros(-3);
        __delay_cycles(100000);
        Reinicio();

}
