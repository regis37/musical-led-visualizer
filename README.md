# Musical LED Visualizer

An Arduino embedded systems project that plays melodies through a passive piezo buzzer and synchronises LEDs with the notes — each LED colour maps to a frequency range.

Built progressively, level by level, as a learning journey through embedded systems engineering.

---

## Project goal

| Feature | Description |
|---------|-------------|
| 🔊 Sound | Play melodies via a passive piezo buzzer |
| 💡 Light | Drive multiple LEDs in sync with the notes |
| 🎨 Mapping | Each frequency range triggers a specific LED colour |
| ⚙️ Learning | Each level introduces new embedded / firmware concepts |

---

## Hardware

- Arduino Uno / Nano (ATmega328P)
- Passive piezo buzzer
- 4 LEDs (Red, Green, Yellow, White)
- 4 × 220 Ω resistors
- Breadboard + jumper wires

---

## Playlist (Level 2+)

| # | Song | Origin |
|---|------|--------|
| 1 | Frère Jacques | French folk song |
| 2 | Happy Birthday | Traditional |
| 3 | Ode to Joy | Beethoven, Symphony No. 9 (1824) |
| 4 | Tetris Theme | Korobeiniki, Russian folk song |
| 5 | Super Mario Bros. Theme | Koji Kondo, Nintendo (1985) |

---

## Levels

| Level | Title | Key concepts |
|-------|-------|-------------|
| [**1 — MVP**](./level1-mvp/) | One note, one LED | GPIO, PWM, `tone()`, `delay()`, struct |
| [**2 — Modular**](./level2-modular/) | Modular architecture + 5-song playlist | `.h`/`.cpp` split, include guards, pointer arrays, `NOTE_REST` sentinel || 3 — Non-blocking | Parallel sound & light | `millis()`, state machine |
| 4 — Hardware timers | Timer-driven architecture | Timer1/2, interrupts |
| 5 — Advanced firmware | MIDI, STM32, RTOS concepts | Bare-metal, multi-tasking |

---

## Author

Regis Tsafack — Elektrotechnik und Informationstechnik, TH Nürnberg
