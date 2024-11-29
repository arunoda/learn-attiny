// More details: https://www.gadgetronicx.com/attiny85-timer-tutorial-generating-time-delay-interrupts/

#include <avr/io.h>

void setupClock() {
  // Following two registries make the counter the normal mode.
  // Which it counts from 0 to 255
  TCCR0A=0x00;
  TCCR0B=0x00;

  // Ask to divide the clock by 1024
  // To make it slower
  // So, counter runs at 1Mhz/1024
  // So, one tick is 1024us
  TCCR0B |= (1<<CS00)|(1<<CS02); 

  // This stores the counter itself
  TCNT0=0;
}

// Here we wait until the counter reaches 255 
// Since our tick is 1024us, so about 261ms
void veryBadDelay() {
  while (TCNT0 != 255)
  {
    
  }

  while (TCNT0 == 255)
  {
    
  }
}

// Our counter sets an overflow bit when it reaches 255.
// So, we can wait for it.
void aBitBadDelay(int waitSec) {
  long cycleTimeMs = 1024L * 255;
  long waitCycles = (waitSec * 1000000) / cycleTimeMs;

  while (waitCycles > 0)
  {
    // Wait until the TOV0 bit is 0
    // This is set by the counter when it reaches to the max
    while((TIFR & (1 << TOV0)) == 0) {

    }
    // Set the bit to 1
    TIFR |= (1 << TOV0);

    waitCycles --;
  }
  
}

int main() {
  // Set the PB1 as output
  DDRB |= (1 << PB1);

  setupClock();

  while(1) {
    // make the light high.
    PORTB |= (1 << PB1);
    
    aBitBadDelay(1);

    // make the light low.
    PORTB &= ~(1 << PB1);

    aBitBadDelay(1);
  }
  return -1;
}