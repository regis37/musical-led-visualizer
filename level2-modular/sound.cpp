// =============================================================
//  sound.cpp — Buzzer module implementation
//
//  YOUR TASK: implement the three functions below.
//  Each function has a description, hints, and the Arduino
//  functions you are allowed to use.
//
//  DO NOT change the function signatures — they must match
//  exactly what sound.h declares, otherwise the linker will
//  throw an error.
// =============================================================

#include "sound.h"
#include "Arduino.h"   // gives access to pinMode, tone, noTone, delay


// ─── TASK 1 ──────────────────────────────────────────────────
//
//  soundInit()
//
//    Configure PIN_BUZZER as an output using pinMode().
//    Make sure no sound is playing at startup using noTone().

void soundInit() {
  pinMode(PIN_BUZZER, OUTPUT);

  noTone(PIN_BUZZER);                    // PWM:  buzzer off


}


// ─── TASK 2 ──────────────────────────────────────────────────
//
//  soundPlay(int freq)
//    Start generating a square wave at the given frequency
//    on PIN_BUZZER. The sound should keep playing until
//    soundStop() is called — do NOT add any delay here.
//
//  Arduino functions to use:
//    tone(pin, frequency)

void soundPlay(int freq) {
  tone(PIN_BUZZER, freq);

}


// ─── TASK 3 ──────────────────────────────────────────────────
//
//  soundStop()
//    Stop any sound currently playing on PIN_BUZZER.
//
//  Arduino functions to use:
//    noTone(pin)

void soundStop() {
  noTone(PIN_BUZZER);                    // PWM:  buzzer off

}


// ─── TASK 4 ──────────────────────────────────────────────────
//
//  soundPlayNote(int freq, int duration)
//
//  What to do:
//    1. Call soundPlay() to start the sound
//    2. Wait for 'duration' milliseconds using delay()
//    3. Call soundStop() to end the sound
//    4. Wait 50 ms of silence (articulation gap between notes)

void soundPlayNote(int freq, int duration) {
  soundPlay(freq);
  delay(duration);
  soundStop();

  // Brief silence between notes (musical articulation).
  // Without this gap, consecutive notes of the same pitch
  // sound like a single long note — the rhythm disappears.
  delay(50);
}
