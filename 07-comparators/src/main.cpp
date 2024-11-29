#include <avr/io.h>
#include <avr/interrupt.h>

void setupTimers() {
  DDRB |= (1 << PB1);
  PORTB |= (1 << PB1);

  // setup timers for normal mode
  TCCR0A = 0;
  TCCR0B = 0;

  // 1024 prescaler
  // We get the overflow by 32.8ms
  TCCR0B |= (1 << CS02) | (1 << CS00);

  // Set the timer to 0
  TCNT0 = 0;

  // Set up CCP mode
  // Comparator will reset the time
  TCCR0A |= (1 << WGM01);

  // Enable global interrupts
  sei();

  // enable comparator intrupts
  TIMSK |= (1 << OCIE0A);

  //Set the comparator to only count to 0
  // That means, every 128us
  OCR0A = 0;

  // //Set the comparator to only count to 255
  // // That means, the full timer, every 32.8ms
  // OCR0A = 255;

}

ISR (TIMER0_COMPA_vect)
{
  PORTB ^= (1 << PB1);
}

int main() {
  setupTimers();

  while(1) {

  }
  return -1;
}