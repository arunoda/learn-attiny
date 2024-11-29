#include <avr/io.h>
#include <avr/interrupt.h>

void setupTimers() {
  DDRB |= (1 << PB0);

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

  // //Set the comparator to only count to 0
  // // That means, every 128us
  // OCR0A = 0;

  //Set the comparator to only count to 255
  // That means, the full timer, every 32.8ms
  OCR0A = 255;

  // Enabling pin toggling
  // So, PB0 will automatically get toggled via the hardware
  // PBO is assigned to OCR0A
  TCCR0A |= (1 << COM0A0);
}

int main() {
  setupTimers();

  while(1) {

  }
  return -1;
}