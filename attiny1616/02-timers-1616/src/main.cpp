#include <avr/io.h>
#include <avr/interrupt.h>

void setupTimer(void)
{
    /* enable global interrupts */
    sei();

    // Enable Intrupts for TCA Single Mode
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    
    // Set it to the normal mode, so it just counts
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    
    // Disable Event Counting. I hope this is input
    TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);
    
    // Even though this is 16bit timer, we can ask it to count
    // to any number
    TCA0.SINGLE.PER = 512;  
    
    // Set the clock divider to 1024
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV1024_gc ;

    // Start the timer
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

    //Here the overflow time is ~79.4ms
    //Here the timer is running with 3.3Mhz clock.
    //(1 / (3300000 / 1024)) * 256 * 10^3 = 79.4ms
}

ISR(TCA0_OVF_vect)
{
    /* Toggle PIN 0 of PORT A */
    PORTA.OUTTGL = PIN1_bm;
    
    /* The interrupt flag has to be cleared manually */
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
    // Set PA1 as a output pin
    PORTA.DIR |= PIN1_bm;
    
    setupTimer();

    
    while (1) 
    {
        ;
    }
}