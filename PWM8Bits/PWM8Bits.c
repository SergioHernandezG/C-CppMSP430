#include <msp430.h> 
#include <msp430.h>
#include <PWM8bits.h>

/**
 * main.c
 */
short duty1=0, duty2=0, duty3=0, ta0=0, ta1=0, count1=0, count2=0, opcion=3, R=256,G=100,B=100,intensidad=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1OUT = 0x00;
    P2OUT = 0x00;
    P1DIR = 0x04;
    P2DIR = 0x7F;

    __PWM0_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA0
    __PWM1_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA1

    __PWM_01_Init(TA01_0, _NON_INVERTED);           //Se configura la Salida 1, del PWM0
    __PWM_01_DutyRegister(duty1);                   // Se manda el duty a utilizar el valores de 0 a 1023

    __PWM_11_Init(TA11_1, _NON_INVERTED);           //Se configura la Salida 1, del PWM1
    __PWM_11_DutyRegister(duty2);                   // Se manda el duty a utilizar el valores de 0 a 1023

    __PWM_12_Init(TA12_0, _NON_INVERTED);           //Se configura la Salida 2, del PWM1
    __PWM_12_DutyRegister(duty3);                   // Se manda el duty a utilizar el valores de 0 a 1023

    while(1)
    {


        switch (opcion)
               {
               case 1:{//color

                   __PWM_01_DutyRegister(duty1=256-R);
                   __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
                   __PWM_12_DutyRegister(duty3=256-B);

                   break;
               }
               case 2:{//intensidad
                   __PWM_01_DutyRegister(duty1=256-R*intensidad/100);
                   __PWM_11_DutyRegister(duty2=256-G*intensidad/100);            //Se incrementa el duty2
                   __PWM_12_DutyRegister(duty3=256-B*intensidad/100);
                   intensidad+=1;
                   if(intensidad>=100)
                       intensidad=0;
                       __delay_cycles(30000);
                   break;

                       }
               case 3:{//estrobo parpadeo

                   __PWM_01_DutyRegister(duty1=256-R);
                   __PWM_11_DutyRegister(duty2=256-G);
                   __PWM_12_DutyRegister(duty3=256-B);
                       __delay_cycles(300000);
                       __PWM_01_DutyRegister(duty1=256);
                       __PWM_11_DutyRegister(duty2=256);
                       __PWM_12_DutyRegister(duty3=256);
                       __delay_cycles(300000);
                   break;

               break;
                       }
               case 4:{//apagar

                   __PWM_01_DutyRegister(duty1=256);
                   __PWM_11_DutyRegister(duty2=256);
                   __PWM_12_DutyRegister(duty3=256);
                           break;
                       }
               default:{

               }





               }

    }
}

//------------------------------ VECTORES DE INTERRUPCION ---------------------------

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    count1++;
    if(count1 == 50)
    {
        ta0 = 1;
        count1 = 0;
    }
    _disable_interrupts();
    LPM0_EXIT;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void)
{
    count2++;
    if(count2 == 50)
    {
        ta1 = 1;
        count2=0;
    }
    _disable_interrupts();
    LPM0_EXIT;
}

