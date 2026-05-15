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

#define NOTE_D5   587
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_G5   784
#define NOTE_A5   880
#define NOTE_Bb4  466

#define NOTE_REST  0    // silence — no frequency
#define NOTE_E4    330


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

const Note FRERE_JACQUES[] = {
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

const int FRERE_JACQUES_LENGTH = sizeof(FRERE_JACQUES) / sizeof(FRERE_JACQUES[0]);

 
// =============================================================
//  SONG 1 — Happy Birthday to You
//  Key: G major | Time: 3/4
// =============================================================
const Note HAPPY_BIRTHDAY[] = {
 
  // "Happy Birth - day  to    you"
  {NOTE_G4,  200},
  {NOTE_G4,  200},
  {NOTE_A4,  400},
  {NOTE_G4,  400},
  {NOTE_C5,  400},
  {NOTE_B4,  800},
 
  // "Happy Birth - day  to    you"
  {NOTE_G4,  200},
  {NOTE_G4,  200},
  {NOTE_A4,  400},
  {NOTE_G4,  400},
  {NOTE_D5,  400},
  {NOTE_C5,  800},
 
  // "Happy Birth - day  dear  [name]..."
  {NOTE_G4,  200},
  {NOTE_G4,  200},
  {NOTE_G5,  400},
  {NOTE_E5,  400},
  {NOTE_C5,  400},
  {NOTE_B4,  400},
  {NOTE_A4,  800},
 
  // "Happy Birth - day  to    you"
  {NOTE_Bb4, 200},
  {NOTE_Bb4, 200},
  {NOTE_A4,  400},
  {NOTE_C5,  400},
  {NOTE_D5,  400},
  {NOTE_C5,  800},
};
const int HAPPY_BIRTHDAY_LENGTH = sizeof(HAPPY_BIRTHDAY) / sizeof(HAPPY_BIRTHDAY[0]);
 
 
// =============================================================
//  SONG 2 — Ode to Joy (Beethoven — Symphony No. 9, 4th mvt)
//  Key: C major | Time: 4/4
//  Public domain — composed 1824
// =============================================================
const Note ODE_TO_JOY[] = {
 
  // Phrase 1
  {NOTE_E4,  300},
  {NOTE_E4,  300},
  {NOTE_F4,  300},
  {NOTE_G4,  300},
  {NOTE_G4,  300},
  {NOTE_F4,  300},
  {NOTE_E4,  300},
  {NOTE_D4,  300},
  {NOTE_C4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  300},
  {NOTE_E4,  500},   // held
  {NOTE_D4,  500},   // held
 
  // Phrase 2 (same, different ending)
  {NOTE_E4,  300},
  {NOTE_E4,  300},
  {NOTE_F4,  300},
  {NOTE_G4,  300},
  {NOTE_G4,  300},
  {NOTE_F4,  300},
  {NOTE_E4,  300},
  {NOTE_D4,  300},
  {NOTE_C4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  300},
  {NOTE_D4,  500},   // held
  {NOTE_C4,  500},   // held
 
  // Phrase 3
  {NOTE_D4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  150},
  {NOTE_F4,  150},
  {NOTE_E4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  150},
  {NOTE_F4,  150},
  {NOTE_E4,  300},
  {NOTE_D4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  500},   // held
 
  // Phrase 4 (reprise of phrase 1)
  {NOTE_E4,  300},
  {NOTE_E4,  300},
  {NOTE_F4,  300},
  {NOTE_G4,  300},
  {NOTE_G4,  300},
  {NOTE_F4,  300},
  {NOTE_E4,  300},
  {NOTE_D4,  300},
  {NOTE_C4,  300},
  {NOTE_C4,  300},
  {NOTE_D4,  300},
  {NOTE_E4,  300},
  {NOTE_D4,  500},   // held
  {NOTE_C4,  500},   // held
};
const int ODE_TO_JOY_LENGTH = sizeof(ODE_TO_JOY) / sizeof(ODE_TO_JOY[0]);
 
 
// =============================================================
//  SONG 3 — Tetris Theme (Korobeiniki)
//  Russian folk song — public domain
//  One of the most recognised melodies in the world.
// =============================================================
const Note TETRIS_THEME[] = {
 
  // Main phrase A
  {NOTE_E5,  300},
  {NOTE_B4,  150},
  {NOTE_C5,  150},
  {NOTE_D5,  300},
  {NOTE_C5,  150},
  {NOTE_B4,  150},
  {NOTE_A4,  300},
  {NOTE_A4,  150},
  {NOTE_C5,  150},
  {NOTE_E5,  300},
  {NOTE_D5,  150},
  {NOTE_C5,  150},
  {NOTE_B4,  450},   // held
  {NOTE_C5,  150},
  {NOTE_D5,  300},
  {NOTE_E5,  300},
  {NOTE_C5,  300},
  {NOTE_A4,  300},
  {NOTE_A4,  500},   // held
 
  // Main phrase B
  {NOTE_D5,  300},
  {NOTE_F5,  150},
  {NOTE_A5,  300},   // 
  {NOTE_G5,  150},
  {NOTE_F5,  150},
  {NOTE_E5,  450},   // held
  {NOTE_C5,  150},
  {NOTE_E5,  300},
  {NOTE_D5,  150},
  {NOTE_C5,  150},
  {NOTE_B4,  300},
  {NOTE_B4,  150},
  {NOTE_C5,  150},
  {NOTE_D5,  300},
  {NOTE_E5,  300},
  {NOTE_C5,  300},
  {NOTE_A4,  300},
  {NOTE_A4,  400},   // held
};
const int TETRIS_THEME_LENGTH = sizeof(TETRIS_THEME) / sizeof(TETRIS_THEME[0]);

// =============================================================
//  SONG 4 — Super Mario Bros. Overworld Theme
//  Composer: Koji Kondo (Nintendo, 1985)
// =============================================================
const Note MARIO_THEME[] = {
  // Opening motif
  {NOTE_E5,  150},
  {NOTE_E5,  150},
  {NOTE_REST,150},
  {NOTE_E5,  150},
  {NOTE_REST,150},
  {NOTE_C5,  150},
  {NOTE_E5,  300},
  {NOTE_G5,  300},
  {NOTE_REST,300},
  {NOTE_G4,  300},
  {NOTE_REST,300},

  // Main melody
  {NOTE_C5,  300},
  {NOTE_REST,150},
  {NOTE_G4,  300},
  {NOTE_REST,150},
  {NOTE_E4,  300},
  {NOTE_REST,150},
  {NOTE_A4,  300},
  {NOTE_B4,  300},
  {NOTE_Bb4, 150},
  {NOTE_A4,  300},
  {NOTE_G4,  200},
  {NOTE_E5,  200},
  {NOTE_G5,  200},
  {NOTE_A5,  300},
  {NOTE_F5,  150},
  {NOTE_G5,  150},
  {NOTE_REST,150},
  {NOTE_E5,  300},
  {NOTE_C5,  150},
  {NOTE_D5,  150},
  {NOTE_B4,  300},
};
const int MARIO_THEME_LENGTH = sizeof(MARIO_THEME) / sizeof(MARIO_THEME[0]);


#endif // MELODY_H
