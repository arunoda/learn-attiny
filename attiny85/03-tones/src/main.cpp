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

int Speaker1 = PIN_PB1;  // Timer1 output pin
int Speaker2 = PIN_PB0;  // Manual output pin for Timer0

volatile bool toneActive = false;

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration) {
  TCCR1 = 0x90 | (11 - octave); // Configure Timer1 for 8 MHz clock
  OCR1C = divisor - 1;          // Set Timer1 compare value
  delay(duration);              // Generate the tone for the specified duration
  TCCR1 = 0x90;                 // Stop Timer1
}

void TinyTone2(unsigned char divisor, unsigned char octave, unsigned long duration) {
  // Configure Timer0 in CTC mode
  TCCR0A = (1 << WGM01);        // CTC mode
  TCCR0B = (1 << CS00) | (octave - 1); // Set prescaler based on octave
  OCR0A = divisor - 1;          // Set Timer0 compare value

  toneActive = true;            // Activate tone output on PB0
  delay(duration);              // Hold the tone for the duration
  toneActive = false;           // Deactivate tone

  TCCR0A = 0x00;                // Stop Timer0
  TCCR0B = 0x00;                // Disable Timer0 clock
}

ISR(TIMER0_COMPA_vect) {
  if (toneActive) {
    PORTB ^= (1 << Speaker2);   // Toggle PB0
  }
}

void setup() {
  pinMode(Speaker1, OUTPUT);
  pinMode(Speaker2, OUTPUT);

  // Enable Timer0 Compare Match Interrupt
  TIMSK |= (1 << OCIE0A);
}

void loop() {
  // Play tone on Speaker1 (PB1) using Timer1
  TinyTone(Note_A, 1, 500);

  // // Play tone on Speaker2 (PB0) using Timer0
  TinyTone2(Note_E, 2, 500);

  // delay(500); // Pause between tones
}
