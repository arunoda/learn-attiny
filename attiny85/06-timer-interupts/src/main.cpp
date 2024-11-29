#include <avr/io.h>
#include <avr/interrupt.h>

void setupTimers() {
  // Timer0 in the normal mode.
  TCCR0A = 0;
  TCCR0B = 0;

  // Divide the main clock by 64
  // So, we will get 2.04ms interrupts
  // (1 / (8000000 / 64)) * 256 * 10^3
  TCCR0B |= (1 << CS01) | (1 << CS00);
  
  // Set the counter value to 0
  TCNT0 = 0;

  // Enable global interrupts
  sei();

  // // Enable Timer0 interrupt
  // After this, delaySec won't work as the clearing the TOVO bit won't be happening
  // So, we might have to intervene
  TIMSK |= (1 << TOIE0);
}

int ticks = 0;
// This will show how long is the cycle.
// Since our tick is 2.04ms, this cycle is about 1s
int cycleTicks = 500;

// Interrupt vector for Timer0
// This will be notified when the timer is finished
// Here this happenes every 2.04ms
ISR (TIMER0_OVF_vect)
{
  if (ticks < cycleTicks/2) {
    PORTB |= (1 << PB1);
  } else {
    PORTB &= ~(1 << PB1);
  }

  ticks++;
  // after 1 sec
  if (ticks == cycleTicks) {
    ticks = 0;
  }
}

int main() {
  DDRB |= (1 << PB1);

  setupTimers();

  PORTB |= (1 << PB1);

  while(1) {
  }
  return -1;
}