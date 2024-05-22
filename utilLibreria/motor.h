#include <msp430.h> 
int sumagrados=0;

void Giros(Grados){
    int i;
    sumagrados=sumagrados+Grados;
    P1OUT &= ~0x0F;
    P1DIR = 0x0F; 
    //gg=Grados;  
    if(Grados<0){
      Grados=Grados*(-1);
       for(i=0;i<5*Grados;i++){
            P1OUT =0x0C;            //paso uno
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
}

void Reinicio(){
    P1OUT &= ~0x0F;
    int i,gradosout=(sumagrados%10);
    if(sumagrados>0){
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
    for(i=0;i<5*(-gradosout);i++){
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
