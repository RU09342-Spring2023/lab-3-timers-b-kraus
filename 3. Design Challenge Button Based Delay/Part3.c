/*
 * Part3.c
 *
 *  Created on: Feb 12, 2023
 *      Author: Beth Kraus
 *
 *      YOU NEED TO FILL IN THIS AUTHOR BLOCK
 */
#include <msp430.h>

void gpioInit();
void timerInit();

void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    gpioInit();
    timerInit();

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);
    void gpioInit(){

        P1OUT &= ~BIT0;
        P1DIR |= BIT0;

        P2OUT |= BIT3;
        P2REN |= BIT3;
        P2IES &= ~BIT3;
        P2IE |= BIT3;
        P2IFG &= ~BIT3;

        P4OUT |= BIT1;
        P4REN |= BIT1;
        P4IES &= ~BIT1;
        P4IE |= BIT1;
        P4IFG &= ~BIT1;
    }

    void timerInit(){
        TB1CCTL0 = CCIE;
        TB1CTL = TBSSEL_1 | MC_2;
        TB1CCR0 = 50000;
    }


    /*
     * INTERRUPT ROUTINES
     */

    // Port 2 interrupt service routine
    #pragma vector=PORT2_VECTOR
    __interrupt void Port_2(void)
    {



    }


    // Port 4 interrupt service routine
       #pragma vector=PORT4_VECTOR
       __interrupt void Port_4(void)
       {



       }
    // Timer B1 interrupt service routine
    #pragma vector = TIMER1_B0_VECTOR
    __interrupt void Timer1_B0_ISR(void)
    {

        }
