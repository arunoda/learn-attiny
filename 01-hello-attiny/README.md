## Hello Attiny

Here we are going to flash a simple Blink command to ATtiny 85 via Arduino UNO as an ISP.

## Setup

Here are the steps we need to do:

### 01. Download Arduino & Setup UNO

Download Arduino & setup it for normal arduino development. Then connect the UNO and flash the example "11.Arduino ISP".

Now our UNO is ready to program ATtiny.

### 02. Setup Platfrom IO

Now add thr PlatformIO Addon to VSCode. After you install the "PlatformIO" addon, install the "Atmel AVR" platform.

### 03. WireUp UNO & Attiny85

* Uno D13 -> Attiny 7
* Uno D12 -> Attiny 6
* Uno D11 -> Attiny 5
* Uno D10 -> Attiny 1

* Uno GND -> Attiny 4
* Uno 5V -> Attiny 8 (You can power externally too. Even 3.3v)

Even though, you setup these pins, you can use them for GPIO purposes.

### 03. Create a New Project

Create a new project and use ATtiny85 as the chip. Then use following as the `platformio.ini`:

```ini
[env:arduino_isp]
platform = atmelavr
framework = arduino
board = attiny85
upload_protocol = stk500v1
; each flag in a new line
upload_flags =
    -P$UPLOAD_PORT
    -b$UPLOAD_SPEED
upload_speed = 19200
upload_port = /dev/cu.usbserial-A5069RR4 ; Set the port to the Arduino COM Port
board_build.f_cpu = 1000000L
```

## Then Use Arduino Code to Program

```c
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
```

Here pin mapping will be as per the physical pins:

* 1 - Reset, PB5
* 2 - PB3
* 3 - PB4, PWM
* 4 - GND
* 5 - PB0, PWM
* 6 - PB1, PWM
* 7 - PB2
* 8 - VCC

## Running at 8Mhz

For this we need to change fuse bits of chip. For that use a AVR Fuse calculator.
Here's how we configure ATtiny85 to run at 8Mhz.

```ini
[env:arduino_isp]
platform = atmelavr
framework = arduino
board = attiny85
upload_protocol = stk500v1
; each flag in a new line
upload_flags =
    -P$UPLOAD_PORT
    -b$UPLOAD_SPEED
    ; here we use a custom AVR fuse settings to run at 8Mhz
    ; use a fuse calculator to change it
    -Ulfuse:w:0xe2:m
    -Uhfuse:w:0xdf:m
    -Uefuse:w:0xff:m
upload_speed = 19200
upload_port = /dev/cu.usbserial-A5069RR4 ; Set the port to the Arduino COM Port
board_build.f_cpu = 8000000L ; set we are running at 8Mhz
```