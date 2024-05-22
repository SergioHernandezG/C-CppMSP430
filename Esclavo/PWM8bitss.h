/*
 * PWM8bits.h
 *
 *  Created on: Jan 22, 2019
 *      Author: GL501VM
 *      Last change: Abdiel 25/01/19
 */

#ifndef PWM8BITS_H_
#define PWM8BITS_H_

#include <msp430.h>
/************************************************************
* SOURCE
************************************************************/
#define _TACLK                              TASSEL_0    /* Timer A clock source select: 0 - TACLK */
#define _ACLK                               TASSEL_1    /* Timer A clock source select: 0 - ACLK */
#define _SMLK                               TASSEL_2    /* Timer A clock source select: 0 - SMCLK */
#define _INCLK                              TASSEL_3    /* Timer A clock source select: 0 - INCLK */

/************************************************************
* PRESCALER
************************************************************/
#define _PRESCALER_1                        ID_0    /* Timer A input divider: 0 - /1 */
#define _PRESCALER_2                        ID_1    /* Timer A input divider: 1 - /2 */
#define _PRESCALER_4                        ID_2    /* Timer A input divider: 2 - /4 */
#define _PRESCALER_8                        ID_3    /* Timer A input divider: 3 - /8 */

/************************************************************
* WAVE_MODE
************************************************************/
#define _FAST_MODE                          MC_1    /* Timer A mode control: 2 - Continous up */
#define _PHASE_CORRECT_MODE                 MC_3    /* Timer A mode control: 3 - Up/Down */

/************************************************************
* INVERTED OR NON INVERTED
************************************************************/
#define _NON_INVERTED                       OUTMOD_6    /* PWM output mode: 6 - PWM toggle/set */
#define _INVERTED                           OUTMOD_6 + OUT         /* PWM output mode: 6 - PWM toggle/set  + PWM Output signal if output mode 0  */

/************************************************************
* CHANNELS
************************************************************/
#define _PWM0_CCR0_CHANNEL                  TA0CCR0  /* Timer A Capture/Compare 0 */
#define _PWM0_CCR1_CHANNEL                  TA0CCR1  /* Timer A Capture/Compare 1 */
#define _PWM0_CCR2_CHANNEL                  TA0CCR2  /* Timer A Capture/Compare 2 */
#define _PWM1_CCR0_CHANNEL                  TA1CCR0  /* Timer A Capture/Compare 0 */
#define _PWM1_CCR1_CHANNEL                  TA1CCR1  /* Timer A Capture/Compare 1 */
#define _PWM1_CCR2_CHANNEL                  TA1CCR2  /* Timer A Capture/Compare 2 */

/************************************************************
* STOP PWM
************************************************************/
#define _PWM_STOP                           OUTMOD_5    /* PWM output mode: 5 - Reset */

/************************************************************
* PORTS
************************************************************/
#define TA00_0                             0x00
#define TA00_1                             0x01
#define TA01_0                             0x02
#define TA01_1                             0x03
#define TA01_2                             0x04

#define TA10_0                             0x05
#define TA10_1                             0x06
#define TA11_0                             0x07
#define TA11_1                             0x08
#define TA12_0                             0x09
#define TA12_1                             0x0A
/*---------------------------------------------------------------------------*/
/* General PWM 16 BITS                                                       */
/*---------------------------------------------------------------------------*/
void    __PWM0_Init(unsigned short source, unsigned short prescaler, unsigned short wave_mode, unsigned short inverted);
void    __PWM0_Duty(unsigned short duty);
void    __PWM0_DutyRegister(unsigned short duty);
void    __PWM0_Stop(void);

void    __PWM1_Init(unsigned short source, unsigned short prescaler, unsigned short wave_mode, unsigned short inverted);
void    __PWM1_Duty(unsigned short duty);
void    __PWM1_DutyRegister(unsigned short duty);
void    __PWM1_Stop(void);

void    __PWM_01_Init(unsigned short port, unsigned short inverted);
void    __PWM_01_Duty(unsigned short duty);
void    __PWM_01_DutyRegister(unsigned short duty);
void    __PWM_01_Stop(void);

void    __PWM_10_Init(unsigned short port, unsigned short inverted);
void    __PWM_10_Duty(unsigned short duty);
void    __PWM_10_DutyRegister(unsigned int duty);
void    __PWM_10_Stop(void);

void    __PWM_11_Init(unsigned short port, unsigned short inverted);
void    __PWM_11_Duty(unsigned short duty);
void    __PWM_11_DutyRegister(unsigned int duty);
void    __PWM_11_Stop(void);


void    __PWM_12_Init(unsigned short port, unsigned short inverted);
void    __PWM_12_Duty(unsigned short duty);
void    __PWM_12_DutyRegister(unsigned int duty);
void    __PWM_12_Stop(void);

/************************************************************
* PWM1
************************************************************/
void    __PWM0_Init(unsigned short source, unsigned short prescaler, unsigned short wave_mode, unsigned short inverted)
{
    TA0CTL = source + wave_mode + prescaler + TACLR;
    TA0CCTL0 = inverted + CCIE;
    TA0CCTL1 = inverted;
    TA0CCR0 = 255;
}

void    __PWM0_Duty(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = (duty*255)/100;
}

void    __PWM0_DutyRegister(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = duty;
}

void    __PWM0_Stop()
{
    TA0R = 0;
    TA0CCTL0 = _PWM_STOP;
    TA0CCTL1 = _PWM_STOP;
}

/************************************************************
* PWM2
************************************************************/
void    __PWM1_Init(unsigned short source, unsigned short prescaler, unsigned short wave_mode, unsigned short inverted)
{
    TA1CTL = source + wave_mode + prescaler + TACLR;
    TA1CCTL0 = inverted ;//+ CCIE;
    TA1CCTL1 = inverted;
    TA1CCTL2 = inverted;
    //TA1CCR0 = 255;
}

void    __PWM1_Duty(unsigned short duty)
{
    _PWM1_CCR1_CHANNEL = (duty*255)/100;
    _PWM1_CCR2_CHANNEL = (duty*255)/100;
}

void    __PWM1_DutyRegister(unsigned short duty)
{
    _PWM1_CCR1_CHANNEL = duty;
    _PWM1_CCR2_CHANNEL = duty;
}

void    __PWM1_Stop()
{
    TA1R = 0;
    TA1CCTL0 = _PWM_STOP;
    TA1CCTL1 = _PWM_STOP;
    TA1CCTL2 = _PWM_STOP;
}


/************************************************************
* PWM_01
************************************************************/
void    __PWM_01_Init(unsigned short port, unsigned short inverted)
{
    TA0CCTL1 = inverted;
    if (port == TA01_0)
    {
        P1DIR |= BIT2;
        P1SEL |= BIT2;
    }
    else if(port == TA01_1)
    {
        P1DIR |= BIT6;
        P1SEL |= BIT6;
    }
    else     if(port == TA01_2)
    {
        P2DIR |= BIT6;
        P2SEL |= BIT6;
        P2SEL &= ~BIT7;


    }
}

void    __PWM_01_Duty(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = (duty*255)/100;
}

void    __PWM_01_DutyRegister(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = duty;
}

void    __PWM_01_Stop()
{
    TA0R = 0;
    TA0CCTL1 = _PWM_STOP;
}

/************************************************************
* PWM_10 ABDIEL
************************************************************/
void  __PWM_10_Init(unsigned short port, unsigned short inverted)
{
    TA0CCTL0 = inverted;
    if (port == TA10_0)
    {
        P2DIR |= BIT0;
        P2SEL |= BIT0;
    }
    else if(port == TA10_1)
    {
        P2DIR |= BIT3;
        P2SEL |= BIT3;
     }
}
void    __PWM_10_Duty(unsigned short duty)
{
    _PWM1_CCR0_CHANNEL = (duty*255)/100;
}

void    __PWM_10_DutyRegister(unsigned int duty)
{
    _PWM1_CCR0_CHANNEL =duty;
}

void    __PWM_10_Stop()
{
    TA1R = 0;
    TA1CCTL0 = _PWM_STOP;
}


/************************************************************
* PWM_11
************************************************************/
void    __PWM_11_Init(unsigned short port, unsigned short inverted)
{
    TA1CCTL1 = inverted;
    if (port == TA11_0)
    {
        P2DIR |= BIT1;
        P2SEL |= BIT1;
    }
    else if(port == TA11_1)
    {
        P2DIR |= BIT2;
        P2SEL |= BIT2;
    }
}

void    __PWM_11_Duty(unsigned short duty)
{
     _PWM1_CCR1_CHANNEL = (duty*255)/100;
}

void    __PWM_11_DutyRegister(unsigned int duty)
{
  //  unsigned int conv =duty*65535/255;
     _PWM1_CCR1_CHANNEL = duty;
}

void    __PWM_11_Stop()
{
    TA1R = 0;
    TA1CCTL1 = _PWM_STOP;
}

/************************************************************
* PWM_12
************************************************************/
void    __PWM_12_Init(unsigned short port, unsigned short inverted)
{
    TA1CCTL2 = inverted;
    if (port == TA12_0)
    {
        P2DIR |= BIT4;
        P2SEL |= BIT4;
    }
    else if(port == TA12_1)
    {
        P2DIR |= BIT5;
        P2SEL |= BIT5;
    }
}

void    __PWM_12_Duty(unsigned short duty)
{
    _PWM1_CCR2_CHANNEL = (duty*255)/100;
}

void    __PWM_12_DutyRegister(unsigned int duty)
{
   // unsigned int conv =duty*65535/255;
    _PWM1_CCR2_CHANNEL = duty; // 65535 ---255
}                              //            duty

void    __PWM_12_Stop()
{
    TA1R = 0;
    TA1CCTL2 = _PWM_STOP;
}


#endif /* PWM8BITS_H_ */