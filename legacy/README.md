# Legacy

Software from the original BQ Zowi that no longer builds or runs with current tools. It is kept for reference.

* `zowi_app/`: firmware for the official Zowi Android app (v2, community edition). It needs the full Zowi
  library (`ZowiSerialCommand`, `sing()`, gestures, mouth...), which is not in this repository.
* `protocoder/`: remote controls written for [Protocoder](https://github.com/victordiaz/protocoder), an
  Android scripting app.
* `remote_swing/`: `swing/` is an Arduino sketch that moves the servos from Bluetooth commands, and
  `accController/` is the Protocoder app that sends them using the phone accelerometer.
* `python-client/`: Python client by Obijuan that drives the oscillators over serial. It needs the
  `Oscillator_server_v2` sketch from the [ArduSnake examples](https://github.com/Obijuan/ArduSnake).
