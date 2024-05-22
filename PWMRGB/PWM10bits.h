/*
 * PWM10bits.h
 *
 *  Created on: Nov 27, 2018
 *      Author: Luis Angel Hernandez Garcia
 */

#ifndef PWM10BITS_H_
#define PWM10BITS_H_


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
#define TA00_0                             0x02 //p1.1
#define TA00_1                             0x20 //p1.5
#define TA01_0                             0x04 //p1.2
#define TA01_1                             0x40 //p1.6
//#define TA01_2                             0x04
#define TA10_0                             0x01 //p2.0
#define TA10_1                             0x40 //p2.6
#define TA10_2                             0x08 //p2.3
#define TA11_0                             0x02 //p2.1
#define TA11_1                             0x04 //p2.2
#define TA12_0                             0x10 //p2.4
#define TA12_1                             0x20 //p2.5


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
void    __PWM_10_DutyRegister(unsigned short duty);
void    __PWM_10_Stop(void);

void    __PWM_11_Init(unsigned short port, unsigned short inverted);
void    __PWM_11_Duty(unsigned short duty);
void    __PWM_11_DutyRegister(unsigned short duty);
void    __PWM_11_Stop(void);

void    __PWM_12_Init(unsigned short port, unsigned short inverted);
void    __PWM_12_Duty(unsigned short duty);
void    __PWM_12_DutyRegister(unsigned short duty);
void    __PWM_12_Stop(void);

/************************************************************
* PWM1
************************************************************/
void    __PWM0_Init(unsigned short source, unsigned short prescaler, unsigned short wave_mode, unsigned short inverted)
{
    TA0CTL = source + wave_mode + prescaler + TACLR;
    TA0CCTL0 = inverted + CCIE;
    TA0CCTL1 = inverted;
    TA0CCR0 = 1023;
}

void    __PWM0_Duty(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = (duty*1023)/100;
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
    TA1CCTL0 = inverted + CCIE;
    TA1CCTL1 = inverted;
    TA1CCR0 = 1023;
}

void    __PWM1_Duty(unsigned short duty)
{
    _PWM1_CCR1_CHANNEL = (duty*1023)/100;
    _PWM1_CCR2_CHANNEL = (duty*1023)/100;
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
void    __PWM_00_Init(unsigned short port, unsigned short inverted)
{
    TA0CCTL1 = inverted;
    if (port == TA00_0)
    {
        P1SEL |=TA00_0;//p1.1
    }
    else if(port == TA00_1)
    {
        P1SEL |= TA00_1; //p1.5  ta0.0
    }

}

void    __PWM_00_Duty(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = (duty*1023)/100;
}

void    __PWM_00_DutyRegister(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = duty;
}

void    __PWM_00_Stop()
{
    TA0R = 0;
    TA0CCTL1 = _PWM_STOP;
}




/************************************************************
* PWM_01
************************************************************/
void    __PWM_01_Init(unsigned short port, unsigned short inverted)
{
    TA0CCTL1 = inverted;
    if (port == TA01_0)
    {
        P1SEL |=TA01_0;//p1.2
    }
    else if(port == TA01_1)
    {
        P1SEL |= TA01_1; //p1.6
    }

}

void    __PWM_01_Duty(unsigned short duty)
{
    _PWM0_CCR1_CHANNEL = (duty*1023)/100;
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
* PWM_10
************************************************************/
void    __PWM_10_Init(unsigned short port, unsigned short inverted)
{
    TA1CCTL1 = inverted;
    if (port == TA10_0)
    {
        P2SEL |=TA10_0;//p2.0
    }
    else if(port == TA10_1)
    {
        P2SEL |= TA10_1; //p2.6
    }
    else if(port == TA10_2)
    {
        P2SEL |= TA10_2; //p2.3
    }
}

void    __PWM_10_Duty(unsigned short duty)
{
     _PWM1_CCR1_CHANNEL = (duty*1023)/100;
}

void    __PWM_10_DutyRegister(unsigned short duty)
{
     _PWM1_CCR1_CHANNEL = duty;
}

void    __PWM_10_Stop()
{
    TA1R = 0;
    TA1CCTL1 = _PWM_STOP;
}

/************************************************************
* PWM_11
************************************************************/
void    __PWM_11_Init(unsigned short port, unsigned short inverted)
{
    TA1CCTL1 = inverted;
    if (port == TA11_0)
    {
        P2SEL |=TA11_0;//p2.1
    }
    else if(port == TA11_1)
    {
        P2SEL |= TA11_1; //p2.2
    }
}

void    __PWM_11_Duty(unsigned short duty)
{
     _PWM1_CCR1_CHANNEL = (duty*1023)/100;
}

void    __PWM_11_DutyRegister(unsigned short duty)
{
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
        P2SEL |= TA12_0; //p2.4
    }
    else if(port == TA12_1)
    {
        P2SEL |= TA12_1; //p2.5
    }
}

void    __PWM_12_Duty(unsigned short duty)
{
    _PWM1_CCR2_CHANNEL = (duty*1023)/100;
}

void    __PWM_12_DutyRegister(unsigned short duty)
{
    _PWM1_CCR2_CHANNEL = duty;
}

void    __PWM_12_Stop()
{
    TA1R = 0;
    TA1CCTL2 = _PWM_STOP;
}


#endif /* PWM10BITS_H_ */
