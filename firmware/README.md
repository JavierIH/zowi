# Firmware

Firmware for the BQ ZUM BT-328 board (ATmega328P, 16 MHz, Arduino framework).

* `lib/Zowi/`: basic movements (walk, turn, updown, moonwalker, swing, crusaito, flapping, jump), with trims
  stored in EEPROM.
* `external/ArduSnake/`: git submodule with [ArduSnake](https://github.com/Obijuan/ArduSnake) by
  Juan Gonzalez-Gomez (Obijuan), which provides the `Oscillator` class. The mods with PlatformIO projects use
  it too. Clone with `git clone --recursive`, or run `git submodule update --init` after cloning.
* `examples/`: `calibration` (set and save the trims), `Oscillator_test1`, `proto` (obstacle avoidance with
  the ultrasonic sensor) and `smooth_criminal` (dance).

Servo pins: YL 2, YR 3, RL 4, RR 5.

## Build with PlatformIO

```
cd firmware
pio run                            # build every sketch
pio run -e calibration -t upload   # build and upload one sketch
```

## Build with the Arduino IDE

Copy `lib/Zowi` and `external/ArduSnake/ArduSnake` to the `libraries/` folder of your sketchbook, install `Servo` from the
library manager and open any sketch in `examples/`.
