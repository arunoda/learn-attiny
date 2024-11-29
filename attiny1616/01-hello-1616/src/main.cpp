#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

void setup() {
  PORTB.DIR |= (1 << PIN4_bp);
  PORTB.OUT |= (1 << PIN4_bp);
}

void loop() {
  PORTB.OUT |= (1 << PIN4_bp);
  _delay_ms(200);
  PORTB.OUT &= ~(1 << PIN4_bp);
  _delay_ms(200);
}