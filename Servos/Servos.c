#include <msp430.h> 

#define MCU_CLOCK           1100000
#define frecuencia_PWM      50      // En Hertz, idealmente son 50Hz.

#define div_servo           180     // 180 grados
#define servo_min           550     // El mínimo ciclo de trabajo
#define servo_max           2350    // El máximo ciclo de trabajo

unsigned int periodo_PWM     = (MCU_CLOCK / frecuencia_PWM);   // Periodo del PWM
unsigned int CT_PWM          = 0;                              // Ciclo de trabajo base

void main (void)
{
    WDTCTL  = WDTPW + WDTHOLD;     // Apaga el WDT

    unsigned int servo_val, servo_act;
    unsigned int servo_grados[div_servo+1];
    unsigned int i=1,j;

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


    //Configuración del primer PWM
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    TACCR0 |= periodo_PWM-1;
    TACCTL1 |= OUTMOD_7;
    TACCR1 |= CT_PWM;
    TACTL |= TASSEL_2 + MC_1;

    //Configura un pin de entrada
    P1IN  |= BIT3;
    P1REN |= BIT3;

    //Ciclo infinito
    while (1)
    {
        // Mueve el servo a la posición máxima
        for (i = 0; i < div_servo; i++)
        {
            TACCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
        // Mueve el servo a la posición mínima
        for (i = div_servo; i > 0; i--)
        {
            TACCR1 = servo_grados[i];
            __delay_cycles(10000);
        }
    //Mueve el servo e distintas posiciones
        // 0 grados
        TACCR1 = servo_grados[i];
        __delay_cycles(600000);
        // 30 grados
        TACCR1 = servo_grados[30];
        __delay_cycles(600000);
        //60 grados
        TACCR1 = servo_grados[60];
        __delay_cycles(600000);
        //90 grados
        TACCR1 = servo_grados[90];
        __delay_cycles(600000);
        //120 grados
        TACCR1 = servo_grados[120];
        __delay_cycles(600000);
        //160 grados
        TACCR1 = servo_grados[160];
        __delay_cycles(600000);
        //45 grados
        TACCR1 = servo_grados[45];
        __delay_cycles(600000);
        //135 grados
        TACCR1 = servo_grados[135];
        __delay_cycles(600000);
        //45 grados
        TACCR1 = servo_grados[45];
        __delay_cycles(600000);
   }
}
