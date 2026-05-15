// =============================================================
//  Musical LED Visualizer — Level 2: Modular Architecture
//
//  Author  : Regis Tsafack
//  Target  : Arduino Uno / Nano (ATmega328P)
//  Created : 2026
//
//  Description:
//    Same behaviour as Level 1, but the code is now split into
//    dedicated modules. This file only orchestrates — it does
//    not contain any hardware logic itself.
//
//  New embedded concepts:
//    - Header files (.h) and implementation files (.cpp)
//    - Include guards (#ifndef / #define / #endif)
//    - Module separation and single responsibility
//    - #define constants for pins and durations
//    - extern declarations for shared data
// =============================================================

#include "melody.h"   // Note struct, MELODY[], MELODY_LENGTH
#include "sound.h"    // soundInit(), soundPlayNote()
#include "led.h"      // ledInit(), ledSetForFrequency(), ledAllOff()


// ─── SETUP ───────────────────────────────────────────────────
//
//  Notice how clean this is compared to Level 1.
//  setup() no longer knows about pin numbers or hardware
//  details — it just tells each module to initialise itself.

void setup() {
  soundInit();
  ledInit();

  Serial.begin(9600);
  Serial.println("=== Musical LED Visualizer — Level 2 ===");
  Serial.print("Melody length: ");
  Serial.print(MELODY_LENGTH);
  Serial.println(" notes");
}


// ─── LOOP ────────────────────────────────────────────────────
//
//  The main loop is also much cleaner: for each note, tell the
//  LED module which frequency is playing, then tell the sound
//  module to play it. No hardware details here at all.

void loop() {
  Serial.println("▶ Playing melody...");

  for (int i = 0; i < MELODY_LENGTH; i++) {
    int freq = MELODY[i].frequency;
    int dur  = MELODY[i].duration;

    Serial.print("  [");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.print(MELODY_LENGTH);
    Serial.print("] ");
    Serial.print(freq);
    Serial.println(" Hz");

    ledSetForFrequency(freq);   // LED module handles the light
    soundPlayNote(freq, dur);   // sound module handles the buzzer
    ledAllOff();                // clean state between notes
  }

  Serial.println("■ Done. Waiting 1.5 s before repeat.\n");
  delay(1500);
}
