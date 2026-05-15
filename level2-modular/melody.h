#ifndef MELODY_H
#define MELODY_H

// =============================================================
//  melody.h — Note definitions and melody storage
//
//  This header is the single source of truth for all musical
//  data. Any file that needs notes or the melody simply does:
//    #include "melody.h"
// =============================================================


// ─── NOTE STRUCTURE ──────────────────────────────────────────
//
//  Defined here (not in main) so every module can use it.
//  sound.cpp needs it to call tone(), led.cpp needs the
//  frequency to pick the right LED.

struct Note {
  int frequency;  // Hz  — pitch of the note
  int duration;   // ms  — how long to play it
};


// ─── FREQUENCY REFERENCE ─────────────────────────────────────
//
//  Standard equal-temperament, A4 = 440 Hz.
//  Use these constants instead of raw numbers in your melody.

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523


// ─── DURATION HELPERS ────────────────────────────────────────
//
//  At ~75 BPM, one beat = 800 ms.
//  These make the melody array much more readable.

#define BEAT_QUARTER  400   // one beat   — standard note
#define BEAT_HALF     700   // held note  — twice as long
#define BEAT_EIGHTH   200   // short note — half a beat


// ─── MELODY ──────────────────────────────────────────────────
//
//  "Frere Jacques" — declared extern so it lives in one place
//  (melody.h) and is shared across all files that include it.
//
//  EMBEDDED NOTE — "extern const":
//    "extern" tells the compiler: "this array is defined
//    somewhere else, just trust it exists."
//    The actual memory allocation happens in melody.h itself
//    (below the extern declaration) using the inline definition.
//    This avoids the multiple-definition linker error you would
//    get if you put a full array definition in a .h file that
//    is included by several .cpp files.

const Note MELODY[] = {
  // Phrase 1: C D E C  |  C D E C
  {NOTE_C4, BEAT_QUARTER},
  {NOTE_D4, BEAT_QUARTER},
  {NOTE_E4, BEAT_QUARTER},
  {NOTE_C4, BEAT_QUARTER},
  {NOTE_C4, BEAT_QUARTER},
  {NOTE_D4, BEAT_QUARTER},
  {NOTE_E4, BEAT_QUARTER},
  {NOTE_C4, BEAT_QUARTER},
  // Phrase 2: E F G(long)  |  E F G(long)
  {NOTE_E4, BEAT_QUARTER},
  {NOTE_F4, BEAT_QUARTER},
  {NOTE_G4, BEAT_HALF},
  {NOTE_E4, BEAT_QUARTER},
  {NOTE_F4, BEAT_QUARTER},
  {NOTE_G4, BEAT_HALF},
};

const int MELODY_LENGTH = sizeof(MELODY) / sizeof(MELODY[0]);


#endif // MELODY_H
