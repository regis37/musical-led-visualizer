// =============================================================
//  Musical LED Visualizer — Level 1: MVP
//
//  Author  : Regis Tsafack
//  Target  : Arduino Uno / Nano (ATmega328P)
//  Created : 2026
//
//  Description:
//    Minimal working version of the Musical LED Visualizer.
//    Plays a short melody through a passive piezo buzzer and
//    lights up the corresponding LED based on the note's
//    frequency range.
//
//  Embedded concepts covered:
//    - GPIO output configuration
//    - PWM signal generation via tone()
//    - Blocking timing with delay()
//    - Frequency-to-color mapping logic
//    - C struct usage on a microcontroller
// =============================================================


// ─── PIN DEFINITIONS ─────────────────────────────────────────
//
//  Best practice: never hardcode pin numbers inside functions.
//  Declare them as constants here so any hardware change only
//  requires editing this one place.
//
//  "const int" in Arduino/AVR is stored in Flash (program memory),
//  not in RAM — important on the ATmega328P which has only 2 KB
//  of SRAM.

const int PIN_BUZZER      = 9;  // Must be a PWM-capable pin (~9 on Uno)
                                 // tone() internally uses Timer2 on AVR

const int PIN_LED_RED     = 2;  // Lights up for low frequencies  (< 350 Hz)
const int PIN_LED_GREEN   = 3;  // Lights up for mid frequencies  (350–550 Hz)
const int PIN_LED_YELLOW  = 4;  // Lights up for high frequencies (550–700 Hz)
const int PIN_LED_WHITE   = 5;  // Lights up for very high freqs  (> 700 Hz)


// ─── NOTE STRUCTURE ──────────────────────────────────────────
//
//  A musical note is fully described by two values: its frequency
//  (which determines the pitch) and its duration (which determines
//  the rhythm). Grouping them in a struct makes the code readable
//  and the data easy to store in an array.
//
//  Embedded note: on AVR, "int" is 16 bits (–32768 to 32767).
//  Frequencies here are well within that range (< 5000 Hz).

struct Note {
  int frequency;  // in Hz  — e.g. 440 for A4 (concert pitch)
  int duration;   // in ms  — e.g. 400 for a quarter note at ~75 BPM
};


// ─── FREQUENCY REFERENCE ─────────────────────────────────────
//
//  Standard equal-temperament frequencies (A4 = 440 Hz tuning):
//
//  Note | Name | Freq (Hz)
//  -----+------+----------
//  C4   | Do   |  262
//  D4   | Re   |  294
//  E4   | Mi   |  330
//  F4   | Fa   |  349
//  G4   | Sol  |  392
//  A4   | La   |  440  ← international reference
//  B4   | Si   |  494
//  C5   | Do   |  523
//  E5   | Mi   |  659
//  G5   | Sol  |  784
//
//  These values come from: f(n) = 440 × 2^((n–49)/12)
//  where n is the MIDI note number.


// ─── MELODY ──────────────────────────────────────────────────
//
//  "Frere Jacques" — first two phrases.
//  Declared globally so it lives in Flash (static storage),
//  not on the stack.
//
//  The pattern:
//    sizeof(array) / sizeof(array[0])
//  is the standard C/C++ idiom for counting elements in a
//  statically-declared array. You will see it everywhere in
//  embedded codebases.

const Note melody[] = {
  // Phrase 1: C D E C  |  C D E C
  {262, 400},  // C4 — Do
  {294, 400},  // D4 — Re
  {330, 400},  // E4 — Mi
  {262, 400},  // C4 — Do
  {262, 400},  // C4 — Do
  {294, 400},  // D4 — Re
  {330, 400},  // E4 — Mi
  {262, 400},  // C4 — Do

  // Phrase 2: E F G(long)  |  E F G(long)
  {330, 400},  // E4 — Mi
  {349, 400},  // F4 — Fa
  {392, 700},  // G4 — Sol (held note)
  {330, 400},  // E4 — Mi
  {349, 400},  // F4 — Fa
  {392, 700},  // G4 — Sol (held note)
};

const int MELODY_LENGTH = sizeof(melody) / sizeof(melody[0]);


// ─── HELPER FUNCTIONS ────────────────────────────────────────

/**
 * Turn off all LEDs.
 * Always bring outputs to a known "safe" state before
 * switching to a new one — a fundamental embedded discipline.
 */
void turnOffAllLeds() {
  digitalWrite(PIN_LED_RED,    LOW);
  digitalWrite(PIN_LED_GREEN,  LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_WHITE,  LOW);
}

/**
 * Light up the LED that corresponds to the given frequency range.
 *
 * This is the "frequency → color" mapping — the core business
 * logic of the project. The thresholds below match the musical
 * register boundaries (bass / mid / treble / very high).
 *
 * @param freq  Frequency of the current note, in Hz.
 */
void lightLedForFrequency(int freq) {
  turnOffAllLeds();

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

/**
 * Play one note and light the corresponding LED simultaneously.
 *
 * HOW tone() WORKS (embedded detail):
 *   tone(pin, freq) programs Timer2 on the ATmega328P to toggle
 *   pin 9 at the given frequency, producing a 50% duty-cycle
 *   square wave. That square wave drives the piezo membrane.
 *   A passive buzzer needs this external oscillator signal —
 *   unlike an active buzzer which has its own oscillator inside.
 *
 * WHY delay() IS BLOCKING:
 *   delay(ms) halts the CPU for exactly ms milliseconds using
 *   a busy-wait loop based on the system tick counter. Nothing
 *   else can run during this time. This is acceptable at Level 1
 *   but will be replaced by millis() at Level 3 (non-blocking
 *   architecture).
 *
 * @param note  A Note struct containing frequency and duration.
 */
void playNote(Note note) {
  lightLedForFrequency(note.frequency);  // GPIO: LED on
  tone(PIN_BUZZER, note.frequency);      // PWM:  buzzer on

  delay(note.duration);                  // blocking wait

  noTone(PIN_BUZZER);                    // PWM:  buzzer off
  turnOffAllLeds();                      // GPIO: LED off

  // Brief silence between notes (musical articulation).
  // Without this gap, consecutive notes of the same pitch
  // sound like a single long note — the rhythm disappears.
  delay(50);
}


// ─── SETUP ───────────────────────────────────────────────────
//
//  setup() runs once on power-on or reset. It is the equivalent
//  of a driver initialisation routine in professional firmware.
//
//  Embedded note — pinMode(pin, OUTPUT):
//    By default every Arduino pin is INPUT (high impedance).
//    We must explicitly configure them as OUTPUT before we can
//    drive them HIGH or LOW.
//    Bare-metal AVR equivalent: DDRB |= (1 << PB1);  (for pin 9)

void setup() {
  // Configure all output pins
  pinMode(PIN_BUZZER,     OUTPUT);
  pinMode(PIN_LED_RED,    OUTPUT);
  pinMode(PIN_LED_GREEN,  OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_WHITE,  OUTPUT);

  // Safe initial state — everything off
  turnOffAllLeds();
  noTone(PIN_BUZZER);

  // Serial monitor — useful for debugging timing and pin states
  Serial.begin(9600);
  Serial.println("=== Musical LED Visualizer — Level 1 ===");
  Serial.print("Melody length: ");
  Serial.print(MELODY_LENGTH);
  Serial.println(" notes");
}


// ─── LOOP ────────────────────────────────────────────────────
//
//  loop() is the firmware super-loop — called indefinitely after
//  setup(). Bare-metal equivalent: while (1) { ... } in main().

void loop() {
  Serial.println("▶ Playing melody...");

  for (int i = 0; i < MELODY_LENGTH; i++) {
    Serial.print("  [");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.print(MELODY_LENGTH);
    Serial.print("] ");
    Serial.print(melody[i].frequency);
    Serial.println(" Hz");

    playNote(melody[i]);
  }

  Serial.println("■ Done. Waiting 1.5 s before repeat.\n");
  delay(1500);  // pause before the melody loops again
}
