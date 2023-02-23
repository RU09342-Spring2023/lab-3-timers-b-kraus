/*
 * Part2.c
 *
 *  Created on: Feb 23, 2023
 *      Author: Beth Kraus
 *
 *      This code will need to change the speed of an LED between 3 different speeds by pressing a button.
 */

#include <msp430.h>
int i=0;
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

}


void gpioInit(){

    P6OUT &= ~BIT6;
    P6DIR |= BIT6;

    P2OUT |= BIT3;
    P2REN |= BIT3;
    P2IES &= ~BIT3;
    P2IE |= BIT3;
    P2IFG &= ~BIT3;
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

    i++;
     P2IFG &= ~BIT3;
     P6IN ^= BIT6;

}


// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    if (i == 1) {
        TB1CCR0 += 5000;
        P6IN ^= BIT6;}
    else if (i == 2) {
        TB1CCR0 += 10000;
        P6IN ^= BIT6;}
    else if (i == 3) {
         TB1CCR0 += 15000;
         P6IN ^= BIT6;}
    else {
        i = 0;}
    }



