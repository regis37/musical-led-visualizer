# Level 1 — MVP: One Note, One LED

> **Musical LED Visualizer** · Arduino embedded systems project

This is the first milestone of the project. The goal is to get something working on hardware as fast as possible — no abstractions, no architecture, just the essential building blocks running together.

---

## What it does

- Plays **"Frère Jacques"** (first two phrases) through a passive piezo buzzer
- Lights up **one LED per note**, chosen by frequency range:

| Frequency range | LED colour | Register |
|----------------|-----------|----------|
| < 350 Hz       | 🔴 Red    | Bass     |
| 350 – 550 Hz   | 🟢 Green  | Mid      |
| 550 – 700 Hz   | 🟡 Yellow | Treble   |
| > 700 Hz       | ⚪ White  | Very high|

---

## Hardware

### Components

| Component | Qty |
|-----------|-----|
| Arduino Uno / Nano | 1 |
| Passive piezo buzzer | 1 |
| Red LED | 1 |
| Green LED | 1 |
| Yellow LED | 1 |
| White LED | 1 |
| 220 Ω resistor | 4 |
| Breadboard | 1 |
| Jumper wires | ~10 |

> ⚠️ Use a **passive buzzer** (no white sticker on top). An active buzzer has its own oscillator and always plays the same pitch — `tone()` won't work correctly with it.

### Wiring

```
Arduino Pin 9  ──────────────── Buzzer (+)
Arduino GND    ──────────────── Buzzer (−)

Arduino Pin 2  ── 220Ω ── Red LED (+)    ── GND
Arduino Pin 3  ── 220Ω ── Green LED (+)  ── GND
Arduino Pin 4  ── 220Ω ── Yellow LED (+) ── GND
Arduino Pin 5  ── 220Ω ── White LED (+)  ── GND
```

> Pin 9 is mandatory for the buzzer — it is one of the hardware PWM pins (`~9` on the Uno silkscreen). `tone()` internally reprograms **Timer2** to generate the square wave.

---

## Embedded concepts introduced

### GPIO — General Purpose Input/Output
By default, all Arduino pins are in `INPUT` mode (high impedance). Before driving a LED or buzzer, the pin must be configured as `OUTPUT` using `pinMode()`. In bare-metal AVR C this maps to:
```c
DDRB |= (1 << PB1);  // set pin 9 as output (Port B, bit 1)
```

### PWM — Pulse Width Modulation
The piezo buzzer works by converting rapid electrical pulses into mechanical vibrations. `tone(pin, frequency)` programs Timer2 on the ATmega328P to toggle pin 9 at the given frequency, producing a 50% duty-cycle **square wave**:
```
HIGH ──┐  ┌──┐  ┌──
       │  │  │  │
  LOW  └──┘  └──┘
       ←────────→
       1 / frequency (period)
```
The faster the square wave, the higher the pitch.

### Blocking delay
`delay(ms)` halts the CPU for exactly `ms` milliseconds using a busy-wait loop. Nothing else can execute during this time. It is simple and predictable — ideal for a first prototype — but **not suitable for production firmware** where the CPU must handle multiple tasks. This limitation is addressed in Level 3 with `millis()`.

### Struct — grouping related data
```cpp
struct Note {
  int frequency;  // Hz — pitch
  int duration;   // ms — rhythm
};
```
Grouping frequency and duration into a single `Note` struct makes the melody array readable and the `playNote()` function self-documenting.

### Frequency-to-color mapping
The mapping is a simple cascade of threshold comparisons:
```
freq < 350      → Red
350 ≤ freq < 550 → Green
550 ≤ freq ≤ 700 → Yellow
freq > 700       → White
```
This is the core "business logic" of the embedded system. In later levels it will be extracted into a lookup table for easier tuning.

---

## How to flash

1. Open `level1-mvp.ino` in the **Arduino IDE**
2. Select board: **Arduino Uno** (or Nano)
3. Select the correct **COM / tty port**
4. Click **Upload** (Ctrl+U)
5. Open **Serial Monitor** at **9600 baud** to follow playback logs

---

## Expected Serial Monitor output

```
=== Musical LED Visualizer — Level 1 ===
Melody length: 14 notes
▶ Playing melody...
  [1/14] 262 Hz
  [2/14] 294 Hz
  [3/14] 330 Hz
  ...
■ Done. Waiting 1.5 s before repeat.
```

---

## Known limitations (addressed in later levels)

| Limitation | Fixed in |
|-----------|---------|
| `delay()` blocks the CPU — nothing else can run during a note | Level 3 |
| All code in one file — hard to maintain as the project grows | Level 2 |
| No way to switch melodies or control playback | Level 2 |
| LEDs just blink on/off — no brightness or animation | Level 2 |

---

## Project structure

```
level1-mvp/
├── level1-mvp.ino   ← main sketch
└── README.md        ← this file
```

---

*Part of the [Musical LED Visualizer](../) Arduino embedded systems project.*
