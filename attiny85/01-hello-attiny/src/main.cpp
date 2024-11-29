#include <Arduino.h>

void setup() {
  pinMode(PIN_PB1, OUTPUT);
}

void loop() {
  digitalWrite(PIN_PB1, HIGH);
  delay(500);
  digitalWrite(PIN_PB1, LOW);
  delay(500);
}