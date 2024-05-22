#include <msp430.h> 

#define MCU_CLOCK           1100000
#define frecuencia_PWM      50      // En Hertz, idealmente son 50Hz.

#define div_servo           180     // Maximum amount of steps in degrees (180 is common)
#define servo_min           550     // El mínimo ciclo de trabajo
#define servo_max           3000    // El máximo ciclo de trabajo

unsigned int periodo_PWM     = (MCU_CLOCK / frecuencia_PWM);   // Periodo del PWM
unsigned int CT_PWM          = 0;                              // Ciclo de trabajo base

void main (void)
{
    WDTCTL  = WDTPW + WDTHOLD;     // Apaga el WDT

    unsigned int servo_val, servo_act;
    unsigned int servo_grados[div_servo+1];
    unsigned int i;

    //Se calcula el valor por grado
    servo_val   = ( (servo_max - servo_min) / div_servo );
    servo_act   = servo_min;
    servo_grados[0] = servo_min;

    //Se declara un vector con los valores para cada ángulo
    for (i = 0; i < div_servo; i++)
    {
        servo_act += servo_val;
        servo_grados[i+1] = servo_act;
    }

    // Configuración de los pines de salida para los PWM
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    P2DIR |= BIT1;
    P2SEL |= BIT1;

    //Configuración del primer PWM
    TA0CCR0 |= periodo_PWM-1;
    TA0CCTL1 |= OUTMOD_7;
    TA0CCR1 |= CT_PWM;
    TA0CTL |= TASSEL_2 + MC_1;

    //Configuración del segundo PWM
    TA1CCR0 |= periodo_PWM-1;
    TA1CCTL1 |= OUTMOD_7;
    TA1CCR1 |= CT_PWM;
    TA1CTL |= TASSEL_2 + MC_1;


    //Ciclo infinito
    while (1)
    {
        // Mueve el servo 1 a la posición máxima
        for (i = 0; i < div_servo; i++)
        {
            TA0CCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
        // Mueve el servo 2 a la posición máxima
        for (i = 0; i < div_servo; i++)
        {
            TA1CCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
        // Mueve el servo 2 a la posición mínima
        for (i = div_servo; i > 0; i--)
        {
            TA1CCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
        // Mueve el servo 1 a la posición mínima
        for (i = div_servo; i > 0; i--)
        {
            TA0CCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
   }
}
