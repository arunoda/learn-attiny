#include <Arduino.h>
/*
  Only PB4(3), PB0(5), PB1(6) supports PWM
*/
#define LED PIN_PB4

void setup() {
  pinMode(LED, OUTPUT);
}

int lc = 0;

void loop() {
  if (lc == 255) {
    lc = 0;
  }

  analogWrite(LED, lc++);
  delay(10);
}