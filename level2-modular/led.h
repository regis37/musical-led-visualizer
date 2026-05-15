#ifndef LED_H
#define LED_H

// =============================================================
//  led.h — LED module interface
//
//  Public contract for everything related to the LEDs.
//  sound.cpp and led.cpp are completely independent — neither
//  includes the other. The main file orchestrates both.
// =============================================================

#define PIN_LED_RED     2
#define PIN_LED_GREEN   3
#define PIN_LED_YELLOW  4
#define PIN_LED_WHITE   5


// ─── PUBLIC FUNCTIONS ────────────────────────────────────────

/**
 * Configure all LED pins as OUTPUT and turn them all off.
 * Must be called once in setup().
 */
void ledInit();

/**
 * Turn off all LEDs.
 * Always call this before lighting a new one — ensures a clean
 * known state before any GPIO transition.
 */
void ledAllOff();

/**
 * Light the LED that matches the given frequency range.
 * Turns off all other LEDs first.
 *
 * Mapping:
 *   freq < 350          → Red    (bass)
 *   350 <= freq < 550   → Green  (mid)
 *   550 <= freq <= 700  → Yellow (treble)
 *   freq > 700          → White  (very high)
 *
 * @param freq  Frequency of the current note in Hz
 */
void ledSetForFrequency(int freq);


#endif // LED_H
