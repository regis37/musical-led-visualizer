// =============================================================
//  led.cpp — LED module implementation
// =============================================================

#include "led.h"
#include "Arduino.h"


void ledInit() {
  pinMode(PIN_LED_RED,    OUTPUT);
  pinMode(PIN_LED_GREEN,  OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_WHITE,  OUTPUT);

  ledAllOff();


}


void ledAllOff() {
  digitalWrite(PIN_LED_RED,    LOW);
  digitalWrite(PIN_LED_GREEN,  LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_WHITE,  LOW);

}


void ledSetForFrequency(int freq) {
  ledAllOff();

  if (freq < 350) {
    digitalWrite(PIN_LED_RED,    HIGH);  // bass register
  } else if (freq < 550) {
    digitalWrite(PIN_LED_GREEN,  HIGH);  // mid register
  } else if (freq <= 700) {
    digitalWrite(PIN_LED_YELLOW, HIGH);  // treble register
  } else {
    digitalWrite(PIN_LED_WHITE,  HIGH);  // very high register
  }

}
