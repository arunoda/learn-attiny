#include <avr/io.h>
#include <Arduino.h>

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
  delay(100);
  
  // set lw
  PORTB &= ~(1 << 1);
  delay(100);
}