#include <msp430.h> 
void Avanza();
void Regresa();
void Reinicio();
int Sentido=0,i,Grados=13;
int main(void)
{
        WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
        P1OUT &= ~0xFF;                           // LIMPIA P1
        P2OUT &= ~0x3F;                           // LIMPIA P2
        P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
        P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA

        if(Grados<0){
            Grados=Grados*(-1);
            Sentido=1;
        }

        if(Sentido==0){
            P1OUT &= ~0x03F;         //lipiar puerto
            Avanza();
        }
        else{
            P1OUT &= ~0x03F;
            Regresa();
        }

        Reinicio();
}
void Avanza(){
    for(i=0;i<5*Grados;i++){
        P1OUT =0x09;         //paso uno
        __delay_cycles(30000);
        P1OUT =0x03;
        __delay_cycles(30000);
        P1OUT =0x06;
        __delay_cycles(30000);
        P1OUT =0x0C;
        __delay_cycles(30000);
    }
}

void Regresa(){
    for(i=0;i<5*Grados;i++){
            P1OUT =0x0C;         //paso uno
            __delay_cycles(30000);
            P1OUT =0x06;
            __delay_cycles(30000);
            P1OUT =0x03;
            __delay_cycles(30000);
            P1OUT =0x09;
            __delay_cycles(30000);
            P1OUT &= ~0x03F;
        }
}
void Reinicio(){

    int gradosout=(Grados%10);
    if(Sentido==0){
    for(i=0;i<5*gradosout;i++){
            P1OUT =0x0C;         //paso uno
            __delay_cycles(30000);
            P1OUT =0x06;
            __delay_cycles(30000);
            P1OUT =0x03;
            __delay_cycles(30000);
            P1OUT =0x09;
            __delay_cycles(30000);
            P1OUT &= ~0x03F;
        }
    }


    else{
    for(i=0;i<5*gradosout;i++){
        P1OUT =0x09;         //paso uno
        __delay_cycles(30000);
        P1OUT =0x03;
        __delay_cycles(30000);
        P1OUT =0x06;
        __delay_cycles(30000);
        P1OUT =0x0C;
        __delay_cycles(30000);
        }
    }

}


