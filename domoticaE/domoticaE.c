#include <msp430.h> 
#include <PWM8bits.h>
#include <motor.h>

void Modos(int opcion);
void Rojo(int col);
void Verde(int colo);
void Azul(int coloo);
void Intensidad(int val);
void Estrobo();

char dato,color;
short duty1=0, duty2=0, duty3=0, ta0=0, ta1=0, count1=0, count2=0, opcion=3;
int bandera=0,con=0,banderaR=0,banderaV=0, banderaA=0;
int valor=0,R=0,G=0,B=0,intensidad=0;

int main(void)
{
     WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
     P1SEL |= BIT6 + BIT7;
     P1SEL2 |=BIT6 + BIT7;
     P1OUT |= BIT0 + BIT2;
     P1DIR |= BIT0 + BIT2;
     P2OUT |= BIT2 + BIT4;                           // LIMPIA P1
     P2DIR |= BIT2 + BIT4;                           // P1.0-P1.6 COMO SALIDA
     UCB0CTL1 |= UCSWRST;
     UCB0CTL0 = UCMODE_3 | UCSYNC;//I2C esclavo
     UCB0I2COA = 0x50;
     UCB0CTL1 &= ~UCSWRST;
     UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable STT and STP interrupt
     IE2 |= UCB0TXIE;                          // Enable TX interrupt

     __PWM0_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA0
     __PWM1_Init(_SMLK, _PRESCALER_1, _FAST_MODE , _NON_INVERTED);   //Se configura el PWM generado por el TimerA1

     __PWM_01_Init(TA01_0, _NON_INVERTED);           //Se configura la Salida 1, del PWM0
     __PWM_11_Init(TA11_1, _NON_INVERTED);           //Se configura la Salida 1, del PWM1
     __PWM_12_Init(TA12_0, _NON_INVERTED);           //Se configura la Salida 2, del PWM1
     __PWM_01_DutyRegister(duty1=256);
     __PWM_11_DutyRegister(duty2=256-G);
     __PWM_12_DutyRegister(duty3=256);
     __delay_cycles(300000);
     __PWM_01_DutyRegister(duty1=256);
     __PWM_11_DutyRegister(duty2=256);
     __PWM_12_DutyRegister(duty3=256);
      __delay_cycles(300000);
     while (1)
     {
         __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts ------sargatiesnuuu chingadere vaa
         __no_operation();                       // Set breakpoint >>here<< and
     }                                        // read out the TXByteCtr counter
}
//-------------Las funciones de Modos------------------
void Modos(opcion){
    switch(opcion){
      case 'a': bandera=0;
      __PWM_01_DutyRegister(duty1=256-R);
      __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
      __PWM_12_DutyRegister(duty3=256-B);
          break;
      case 'r':bandera=1;
      __PWM_01_DutyRegister(duty1=256-R);
      __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
      __PWM_12_DutyRegister(duty3=256-B);
            break;
      case 'g':bandera=2;
      __PWM_01_DutyRegister(duty1=256-R);
      __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
      __PWM_12_DutyRegister(duty3=256-B);
         break;
      case 'z':bandera=3;
      __PWM_01_DutyRegister(duty1=256-R);
      __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
      __PWM_12_DutyRegister(duty3=256-B);
          break;
      case 'b': bandera=4;
          //Intensidad(1);
          break;
      case 'c':bandera=0;
          Estrobo();
          break;
      case 'd': bandera=0;
          P1OUT =  0x01;//apagado
         intensidad=0;
       __PWM_01_DutyRegister(256);
       __PWM_11_DutyRegister(256);            //Se incrementa el duty2
       __PWM_12_DutyRegister(256);
          break;
       default : break;//apagado
                                }
}

void Rojo(col){
    P1OUT &=  ~0x01;//encendido}
    intensidad=0;
    bandera=0;
    R=col;
    __PWM_01_DutyRegister(duty1=256-R);
    __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
    __PWM_12_DutyRegister(duty3=256-B);
}
void Verde(colo){
    P1OUT =  0x01;//encendido}
    intensidad=0;
    bandera=0;
    G=colo;
    __PWM_01_DutyRegister(duty1=256-R);
    __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
    __PWM_12_DutyRegister(duty3=256-B);
}
void Azul(coloo){
    P1OUT &=  ~0x01;//encendido}
    intensidad=0;
    bandera=0;
    B=coloo;
    __PWM_01_DutyRegister(duty1=256-R);
    __PWM_11_DutyRegister(duty2=256-G);            //Se incrementa el duty2
    __PWM_12_DutyRegister(duty3=256-B);
}
void Intensidad(val){
    P1OUT =  0x01;//encendido}
     bandera=0;
   /* __PWM_01_DutyRegister(duty1=256-R*val/100);
    __PWM_11_DutyRegister(duty2=256-G*val/100);            //Se incrementa el duty2
    __PWM_12_DutyRegister(duty3=256-B*val/100);
   */
    __PWM_01_DutyRegister(duty1=256-R*intensidad/100);
    __PWM_11_DutyRegister(duty2=256-G*intensidad/100);            //Se incrementa el duty2
    __PWM_12_DutyRegister(duty3=256-B*intensidad/100);
        intensidad+=1;
         //intensidad=val;
       if(intensidad>=100)
         intensidad=0;
        __delay_cycles(30000);
}

void Estrobo(){
    P1OUT &=  ~0x01;
    intensidad=0;
    bandera=0;
    Giros(-5);
    __delay_cycles(100000);
    Reinicio();
}
//--------------------------------interrupciones--------------fint-ree-rcuan lanii-chi-ni sein thi leetr-----------
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    P1OUT =  0x01;
    dato= UCB0RXBUF; //lee el dato de entrada
    Modos(dato);
    if(bandera>0){
        valor=0;
    switch(bandera){
      case 1:valor=dato;
          Rojo(valor);
       break;
      case 2:valor=dato;
          Verde(valor);
       break;
      case 3:valor=dato;
          Azul(valor);
      break;
      case 4:valor=dato;
          Intensidad(valor);
      break;
      default:break;
    }
    }
    if(bandera==0){
    Modos(dato);
   }
    LPM0_EXIT;  // sale de LPM0 (OPCIONAL)
}

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
///Autor: Serch
///www.serch.com
