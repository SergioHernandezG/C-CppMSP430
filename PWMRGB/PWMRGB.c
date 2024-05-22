#include <msp430.h> 
#include <PWM10bits.h>
short duty1=0, duty2=0, duty3=1023, ta0=0, ta1=0, count1=0, count2=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1OUT = 0x00;
    P2OUT = 0x00;
    P1DIR = 0x66;
    P2DIR = 0x7F;

    __PWM0_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA0
    __PWM1_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA1

    __PWM_11_Init(TA11_1, _NON_INVERTED);           //Se configura la Salida 1, del PWM0 puerto p2.0
    __PWM_10_DutyRegister(duty1);                   // Se manda el duty a utilizar el valores de 0 a 1023

    __PWM_11_Init(TA11_0, _NON_INVERTED);           //Se configura la Salida 1, del PWM0 P2.1
    __PWM_11_DutyRegister(duty2);                   // Se manda el duty a utilizar el valores de 0 a 1023

    __PWM_12_Init(TA12_0, _NON_INVERTED);           //Se configura la Salida 1, del PWM0 puerto p2.4
    __PWM_12_Duty(duty3);                   // Se manda el duty a utilizar el valores de 0 a 1023

    //__PWM_11_Init(TA11_0, _NON_INVERTED);           //Se configura la Salida 1, del PWM1
  //  __PWM_11_DutyRegister(duty2);                   // Se manda el duty a utilizar el valores de 0 a 1023
  //  __PWM_11_Init(TA01_2, _NON_INVERTED);           //Se configura la Salida 1, del PWM1 puerto p1.3
  //  __PWM_11_Duty(duty2);                   // Se manda el duty a utilizar el valores de 0 a 1023

    //__PWM_12_Init(TA11_1, _NON_INVERTED);           //Se configura la Salida 2, del PWM1
   // __PWM_12_Duty(duty3);                   // Se manda el duty a utilizar el valores de 0 a 1023
   // __PWM_12_Init(TA12_0, _NON_INVERTED);           //Se configura la Salida 2, del PWM1
    //__PWM_12_DutyRegister(duty3);                   // Se manda el duty a utilizar el valores de 0 a 1023

    /*while(1)
    {
        _enable_interrupts();                           //Habilitar interrupciones
        LPM0;                                           //Habilitar LPM0
        if (ta0 == 1)                                   //Si hay interrupcion por timerA0
        {
            __PWM_01_Duty(duty1+=1);            //Se incrementa el duty1
            ta0=0;                                      //Se limpia la bandera
        }
        if (ta1 == 1)                                   //Si hay interrupcion por timerA1
        {
            __PWM_10_Duty(duty1+=10);
            __PWM_11_Duty(duty2+=15);            //Se incrementa el duty2
            __PWM_12_Duty(duty3+=8);            //Se incrementa el duty3
            ta1=0;                                      //Se limpia la bandera
        }

        if(duty1>1023)
            duty1=0;                    //Se limpia la variable
        if(duty2>1023)
            duty2=0;                    //Se limpia la variable
        if(duty3>1023)
            duty3=0;                    //Se limpia la variable
    }*/
}

//------------------------------ VECTORES DE INTERRUPCION ---------------------------

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
    count1++;
    if(count1 ==10)//200
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
    if(count2 == 100)
    {
        ta1 = 1;
        count2=0;
    }
    _disable_interrupts();
    LPM0_EXIT;
}

