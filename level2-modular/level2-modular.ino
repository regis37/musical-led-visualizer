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


// ─── PLAYLIST ────────────────────────────────────────────────
//
//  A pointer array — each entry points to one melody in memory.
//  To add or remove a song: edit only this section.
//
//  EMBEDDED CONCEPT — array of pointers:
//    Instead of copying data, we store addresses.
//    Each "const Note*" is just a memory address (2 bytes on AVR)
//    pointing to the actual array stored in Flash.

const Note* PLAYLIST[] = { FRERE_JACQUES,        HAPPY_BIRTHDAY,       ODE_TO_JOY,       TETRIS_THEME,      MARIO_THEME       };
const int   LENGTHS[]  = { FRERE_JACQUES_LENGTH,  HAPPY_BIRTHDAY_LENGTH, ODE_TO_JOY_LENGTH, TETRIS_THEME_LENGTH, MARIO_THEME_LENGTH };
const char* NAMES[]    = { "Frere Jacques",       "Happy Birthday",      "Ode to Joy",      "Tetris Theme",    "Mario Theme"     };

const int PLAYLIST_SIZE = sizeof(PLAYLIST) / sizeof(PLAYLIST[0]);



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
  Serial.print(PLAYLIST_SIZE);
  Serial.println(" songs in playlist");
}


// ─── LOOP ────────────────────────────────────────────────────
//
//  The main loop is also much cleaner: for each note, tell the
//  LED module which frequency is playing, then tell the sound
//  module to play it. No hardware details here at all.

void loop() {
  for (int song = 0; song < PLAYLIST_SIZE; song++) {

    const Note* melody = PLAYLIST[song];
    int         length = LENGTHS[song];

    Serial.print("▶ Now playing: ");
    Serial.println(NAMES[song]);

    for (int i = 0; i < length; i++) {
      ledSetForFrequency(melody[i].frequency);
      soundPlayNote(melody[i].frequency, melody[i].duration);
      ledAllOff();
    }

    Serial.println("■ Done.\n");
    delay(1500);  // pause between songs
  }
  // loop() restarts automatically → playlist repeats
}
