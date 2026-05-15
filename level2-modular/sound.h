#ifndef SOUND_H
#define SOUND_H

// =============================================================
//  sound.h — Buzzer module interface
//
//  This header is the PUBLIC CONTRACT of the sound module.
//  It declares WHAT the module can do, without revealing HOW.
//  Any file that needs sound just does: #include "sound.h"
//
//  EMBEDDED CONCEPT — Header / Implementation split:
//    .h  = declaration  → what exists, what it takes, what it returns
//    .cpp = definition  → the actual code that runs on the MCU
//
//  This mirrors how professional firmware drivers are structured:
//    uart.h   → API (what you call)
//    uart.cpp → driver implementation (how it works)
// =============================================================

#define PIN_BUZZER 9  // Must be a PWM pin — tone() uses Timer2


// ─── PUBLIC FUNCTIONS ────────────────────────────────────────
//
//  These are the only functions other modules are allowed to
//  call. Everything else stays private inside sound.cpp.

/**
 * Configure the buzzer pin as OUTPUT.
 * Must be called once in setup() before any sound is played.
 */
void soundInit();

/**
 * Start playing a frequency on the buzzer (non-blocking call).
 * The sound continues until soundStop() is called.
 *
 * @param freq  Frequency in Hz (e.g. 440 for A4)
 */
void soundPlay(int freq);

/**
 * Stop any sound currently playing on the buzzer.
 */
void soundStop();

/**
 * Play a complete note: sound ON for duration ms, then OFF.
 * Includes a short silence gap after the note for articulation.
 * This call BLOCKS for (duration + 50) ms total.
 *
 * @param freq      Frequency in Hz
 * @param duration  Duration in ms
 */
void soundPlayNote(int freq, int duration);


#endif // SOUND_H
