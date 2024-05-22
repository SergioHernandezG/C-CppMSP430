#include <msp430.h> 
void Avanza();
void Regresa();
int conteo=0,cont=0,display=0,vuelta=0,Espera=0x2F34,ang1=200,ang2=200,vel=0x016A;
int main(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT

       // BCSCTL1 |= DIVA_0;                        // ACLK /1
       // BCSCTL3 |= LFXT1S_2;                      // SE CONFIGURA VLO
       // CCR0 = 1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA

        TACCR0 = 30;                              // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
        TACCTL0 |= CCIE;                          // INTERRUPCION EN MODO COMPARADOR
        TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
        P1OUT &= ~0xFF;                           // LIMPIA P1
        P2OUT &= ~0x3F;                           // LIMPIA P2
        P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
        P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
        while(1)
        {
               __bis_SR_register(LPM0_bits + GIE);       // LPM0+INTERRUPCION

                if(conteo<Espera){// 2f34(cristal) ESPERA DOS SEGUNDOS ANTES DE EMPEZAR A GIRAR
                    conteo++;
                }
                if(vuelta==(ang1+ang2)){//190(CRISTAL)SI DIO UNA VUELTA COMPLETEA...200
                    P1OUT &= ~0x03F;
                    vuelta=0;
                    conteo=0;
                }
                if(conteo==Espera){ //2f34(cristal)EMPIEZA A GIRAR UNA VUELTA..12068
                    cont++;
                    if(cont==vel){//B5(CRISTAL)30 mS POR CADA 1.8 GRADOS QUE GIRA EL MOTOR
                        vuelta++;
                        if(vuelta>=ang1){//C7(CRISTAL)
                            Regresa();
                        }
                        else Avanza();
                 }
                }
        }
}
void Avanza(){
    cont=0;
    switch (display)
                           {
                               case 0: display ++;
                                       P1OUT =0x09;
                                       break;
                               case 1: display ++;
                                       P1OUT =0x03;
                                       break;
                               case 2: display ++;
                                       P1OUT =0x06;
                                       break;
                               default: display=0;
                                       P1OUT =0x0C;
                                       break;
                           }

}

void Regresa(){
    cont=0;
    switch (display)
                           {
                               case 0: display ++;
                                       P1OUT =0x0C;
                                       break;
                               case 1: display ++;
                                       P1OUT =0x06;
                                       break;
                               case 2: display ++;
                                       P1OUT =0x03;
                                       break;
                               default: display=0;
                                       P1OUT =0x09;
                                       break;
                           }

}
//-------------------------interrupciones

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    LPM0_EXIT;                            // SALE DE LPM3
    //display();
}
