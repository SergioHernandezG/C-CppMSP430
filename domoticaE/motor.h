#include <msp430.h> 
int sumagrados=0;

void Giros(Grados){
    int i;
    sumagrados=sumagrados+Grados;
    P2OUT &= ~0x2B;
    P2DIR = 0x2B;
    //gg=Grados;  
    if(Grados<0){
      Grados=Grados*(-1);
       for(i=0;i<5*Grados;i++){
            P2OUT =0x28;            //paso uno
            __delay_cycles(30000);
            P2OUT =0x0A;
            __delay_cycles(30000);
            P2OUT =0x03;
            __delay_cycles(30000);
            P2OUT =0x21;
            __delay_cycles(30000);
            P2OUT &= ~0x2B;
        } 
      } 
    else{                    
    for(i=0;i<5*Grados;i++){
        P2OUT =0x21;         //paso uno
        __delay_cycles(30000);
        P2OUT =0x03;
        __delay_cycles(30000);
        P2OUT =0x0A;
        __delay_cycles(30000);
        P2OUT =0x28;
        __delay_cycles(30000);
    }
 }
}

void Reinicio(){
    P2OUT &= ~0x02B;
    int i,gradosout=(sumagrados);
    if(sumagrados>0){
    for(i=0;i<5*gradosout;i++){
            P2OUT =0x28;         //paso uno
            __delay_cycles(30000);
            P2OUT =0x0A;
            __delay_cycles(30000);
            P2OUT =0x03;
            __delay_cycles(30000);
            P2OUT =0x21;
            __delay_cycles(30000);
            P2OUT &= ~0x02B;
        }
    }


    else{
    for(i=0;i<5*(-gradosout);i++){
        P2OUT =0x21;         //paso uno
        __delay_cycles(30000);
        P2OUT =0x03;
        __delay_cycles(30000);
        P2OUT =0x0A;
        __delay_cycles(30000);
        P2OUT =0x28;
        __delay_cycles(30000);
        }
    }

    sumagrados=0;

}

