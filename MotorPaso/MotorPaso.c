#include <msp430.h> 
void Avanza();
void Regresa();
int conteo=0,cont=0,display=0,vuelta=0;
int main(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
                             // SE HABILITA LA INTERRUPCION POR WDT
        BCSCTL1 |= DIVA_0;                        // ACLK /1
        BCSCTL3 |= LFXT1S_2;                      // SE CONFIGURA VLO
        CCR0 = 1;                                 // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
        CCTL0 = CCIE;                             // INTERRUPCION EN MODO COMPARADOR
        TACTL = TASSEL_1|ID_0|MC_1;               // TACLK = TACLK, /1, Up mode, IE
        P1OUT &= ~0xFF;                           // LIMPIA P1
        P2OUT &= ~0x3F;                           // LIMPIA P2
        P1DIR = 0x7F;                             // P1.0-P1.6 COMO SALIDA
        P2DIR = 0x3F;                             // P2.0-P1.5 COMO SALIDA
        while(1)
        {
               __bis_SR_register(LPM0_bits + GIE);       // LPM0+INTERRUPCION

                if(conteo<0x2F34){//  ESPERA DOS SEGUNDOS ANTES DE EMPEZAR A GIRAR
                    conteo++;
                }
                if(vuelta==0x190){//SI DIO UNA VUELTA COMPLETEA...200
                    P1OUT &= ~0x03F;
                    vuelta=0;
                    conteo=0;
                }
                if(conteo==0x2F34){ //EMPIEZA A GIRAR UNA VUELTA..12068
                    cont++;
                    if(cont==0x0B5){//30 mS POR CADA 1.8 GRADOS QUE GIRA EL MOTOR
                        vuelta++;
                        if(vuelta>0x0C7){
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
