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

## Levels

| Level | Title | Key concepts |
|-------|-------|-------------|
| [**1 — MVP**](./level1-mvp/) | One note, one LED | GPIO, PWM, `tone()`, `delay()`, struct |
| 2 — Modular | Full melody + LED effects | Functions, arrays, modular code |
| 3 — Non-blocking | Parallel sound & light | `millis()`, state machine |
| 4 — Hardware timers | Timer-driven architecture | Timer1/2, interrupts |
| 5 — Advanced firmware | MIDI, STM32, RTOS concepts | Bare-metal, multi-tasking |

---

## Author

Regis Tsafack — Elektrotechnik und Informationstechnik, TH Nürnberg
