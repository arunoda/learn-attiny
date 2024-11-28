#include <avr/io.h>
#include <util/delay.h>

void setup() {
  //inputs
  DDRB &= ~(1 << 3);
  PORTB |= (1 << 3); // this activates the internal pull-up resistor

  // outputs
  DDRB |= (1 << 1); // pin 6
  DDRB |= (1 << 0); // pin 5
}

void loop() {
  if (PINB & (1 << 3)) {  // pin 2
    PORTB |= (1 << 0);
  } else {
    PORTB &= ~(1 << 0);
  }

  // set high
  PORTB |= (1 << 1);
  _delay_ms(100);
  
  // set lw
  PORTB &= ~(1 << 1);
  _delay_ms(100);
}

int main() {
  setup();
  while (1)
  {
    loop();
  }
  return -1;
}