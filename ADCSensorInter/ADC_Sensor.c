//EL ADC TRABAJA CON EL SENSOR INTERNO DE TERMPERATURA, DETECTA UN INCREMENTO DE
//TEMPERATURA.
//LA TEMPERATURA DEL SENSOR ES MUESTREADA APROX. CADA 120MS Y ES COMPARADO
// CON UN VALOR DELTA USANDO UNA ISR.
//LA DIVISION DE (ADC10OSC/4)/64 DETERMINA EL TIEMPO DE MUESTREO NECESARIO
//DE POCO MAS DE 30US PARA LA TEMPERATURA DEL SENSOR.
//EL ADC OPERA EN MODO DE CANAL SIMPLE DE MANERA REPETIDA Y SE REALIZA DESDE EL
//TIMER A CCR1
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.2MHz, ADC10CLK = ADC10OSC
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10          P1.0|-->LED
#include <msp430.h> 
static unsigned int FirstADCVal;            // PARA ALMACENAR EL RESULTADO DEL ADC

#define ADCDeltaOn       3                  // ~ 2 Deg C APROX. (DELTA)

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // DETIENE EL WDT
  ADC10CTL1 = ADC10DIV_3 + INCH_10 + SHS_1 + CONSEQ_2;  // ADC DESDE EL TA, TRABAJA DE MANERA REPETIDA EL A10
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REF2_5V + ADC10IE + REFON + ADC10ON;
  __enable_interrupt();                     // HABILITA LAS INTERRUPCIONES
  TACCR0 = 30;                              // TIEMPO DE ESTABLECIMIENTO DE REF EXTERNA
  TACCTL0 |= CCIE;                          // INTERRUPCION EN MODO COMPARADOR
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // ESPERA EN LPM0 LA INTERRUPCION
  TACCTL0 &= ~CCIE;                         // DESHABILITA LA INTERRUPCION POR EL COMPARADOR
  __disable_interrupt();
  ADC10CTL0 |= ENC;
  TACCTL1 = OUTMOD_4;                       // MODO TOGGLEO DEL TIMER
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, MODO DE CONTINUO
  while (!(ADC10IFG & ADC10CTL0));          // ES LA PRIMERA CONVERSION?
  FirstADCVal = ADC10MEM;                   // LEE EL VALOR DEL ADC
  P1OUT = 0x00;                             // LIMPIA P1
  P1DIR = 0x01;                             // P1.0 COMO SALIDA
  __bis_SR_register(LPM0_bits + GIE);       // LPM0+INTERRUPCION
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  if (ADC10MEM >= FirstADCVal + ADCDeltaOn)
    P1OUT |= 0x01;                          // LED on
  else
    P1OUT &= ~0x01;                         // LED off
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}
