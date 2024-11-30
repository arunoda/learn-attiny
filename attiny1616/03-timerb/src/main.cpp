#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void setupTCBInterrupt() {
    TCB0.CCMP = 65535; // Set the compare value
    TCB0.CTRLA |= TCB_ENABLE_bm; // counting value

    // Uses 20Mhz clock & divide it by for here
    TCB0.CTRLA |= TCB_CLKSEL_CLKDIV2_gc; // clock div by 2
  
    // Enabling inturrupts
    TCB0.CTRLB |= TCB_CNTMODE_INT_gc; // Timer interrupt mode (periodic interrupts)
    TCB0.INTCTRL = TCB_CAPT_bm; // Enable Capture interrupt
    sei();
}

// TCB0 Interrupt Service Routine
int tcb0SubScalerCnt = 0;
ISR(TCB0_INT_vect) {
  // Here with 20Mhz clock speed & 2div clockdiv 
  // we cannot acheive 20Hz
  // That's why we are manually subscaling here
  // NOTE: Do not use tcb0SubScalerCnt++ == 4 here. I will affect the timer
  if (tcb0SubScalerCnt == 4) {
    tcb0SubScalerCnt = 0;
    PORTA.OUTTGL = PIN1_bm;
  }

  tcb0SubScalerCnt++;

  // Clear the interrupt flag
  TCB0.INTFLAGS = TCB_CAPT_bm;
}

void setup() {
    // Set PA1 as output (for toggling an LED)
    PORTA.DIRSET = PIN1_bm;

    // Set PA2 as input
    PORTA.DIRCLR = PIN2_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;

    // Configure TCB0 with interrupts
    setupTCBInterrupt();
}

void loop() {
    if(PORTA.IN & PIN2_bm) {
      TCB0.CCMP = 30000;
    } else {
      TCB0.CCMP = 60000;
    }
}
