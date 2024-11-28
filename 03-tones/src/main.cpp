#include <Arduino.h>

/* TinyTone for ATtiny85 */

// Notes
const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;

int Speaker = PIN_PB1;

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
  // TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}

void setup()
{
  pinMode(Speaker, OUTPUT);
}

void loop()
{ 
  // We can also use Arduino tone() library
  TinyTone(Note_A, 1, 500);
}


