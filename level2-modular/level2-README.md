# Level 2 — Modular Architecture + Playlist

> **Musical LED Visualizer** · Arduino embedded systems project

Building on Level 1, this milestone restructures the entire codebase into dedicated modules and introduces a multi-song playlist system.

---

## What's new vs Level 1

| Feature | Level 1 | Level 2 |
|---------|---------|---------|
| Code structure | Single `.ino` file | Separated modules (`.h` / `.cpp`) |
| Melodies | Frère Jacques only | 5-song playlist |
| Song switching | Edit everywhere | Change one line |
| Silence support | No | `NOTE_REST` sentinel value |
| Memory usage | Copies data | Pointer array — zero copy |

---

## What it does

Plays a playlist of 5 songs in a loop, lighting the correct LED for each note's frequency range:

| Song | Origin |
|------|--------|
| Frère Jacques | French folk song |
| Happy Birthday | Traditional |
| Ode to Joy | Beethoven, Symphony No. 9 (1824) |
| Tetris Theme | Korobeiniki, Russian folk song |
| Super Mario Bros. Theme | Koji Kondo, Nintendo (1985) |

---

## File structure

```
level2-modular/
├── level2-modular.ino   ← main: playlist, setup(), loop()
├── melody.h             ← Note struct, frequency #defines, all melodies
├── sound.h              ← buzzer module interface
├── sound.cpp            ← buzzer module implementation
├── led.h                ← LED module interface
└── led.cpp              ← LED module implementation
```

---

## Hardware

Same as Level 1 — no changes required.

| Component | Qty |
|-----------|-----|
| Arduino Uno / Nano | 1 |
| Passive piezo buzzer | 1 |
| LEDs (Red, Green, Yellow, White) | 4 |
| 220 Ω resistors | 4 |
| Breadboard + jumper wires | — |

---

## Embedded concepts introduced

### Header / Implementation split
Each module has two files:
- `.h` — the **public contract** (what the module offers)
- `.cpp` — the **implementation** (how it works internally)

```cpp
// sound.h — declaration only
void soundPlayNote(int freq, int duration);

// sound.cpp — implementation
void soundPlayNote(int freq, int duration) {
  soundPlay(freq);
  delay(duration);
  soundStop();
  delay(50);
}
```

Any file that needs the buzzer simply does `#include "sound.h"` — it never sees the implementation details.

### Include guards
Every `.h` file starts with:
```cpp
#ifndef SOUND_H
#define SOUND_H
// ... declarations ...
#endif // SOUND_H
```
This prevents the compiler from processing the same header twice when multiple files include it — a mandatory practice in any C/C++ codebase.

### Array of pointers — playlist system
```cpp
const Note* PLAYLIST[] = { FRERE_JACQUES, HAPPY_BIRTHDAY, ODE_TO_JOY, ... };
```
Each entry is a **pointer** (a memory address), not a copy of the data. On AVR, a pointer is 2 bytes regardless of how large the array it points to is. Adding a new song costs 2 bytes of RAM — the melody itself stays in Flash.

### Sentinel value — NOTE_REST
```cpp
#define NOTE_REST  0

void soundPlayNote(int freq, int duration) {
  if (freq == NOTE_REST) {
    delay(duration);   // silence — no buzzer
  } else {
    soundPlay(freq);
    delay(duration);
    soundStop();
  }
  delay(50);
}
```
`NOTE_REST = 0` is a **sentinel value** — a special value that carries meaning within the data stream. Used to encode silences directly inside the melody array without changing the `Note` struct.

---

## How to add a new song

1. Add any missing note `#define`s in `melody.h`
2. Declare the melody array in `melody.h` before `#endif`
3. Add it to the three playlist arrays in `level2-modular.ino`

```cpp
// level2-modular.ino — only these three lines change
const Note* PLAYLIST[] = { ..., MY_NEW_SONG       };
const int   LENGTHS[]  = { ..., MY_NEW_SONG_LENGTH };
const char* NAMES[]    = { ..., "My New Song"      };
```

---

## Known limitations (addressed in later levels)

| Limitation | Fixed in |
|-----------|---------|
| `delay()` blocks the CPU — no parallel tasks during notes | Level 3 |
| LEDs only on/off — no animation or brightness effects | Level 3 |
| No user input (buttons, potentiometer) | Level 4 |

---

*Part of the [Musical LED Visualizer](../) Arduino embedded systems project.*
