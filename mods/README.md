# Zowi mods

Each mod follows the same layout: `hardware/` (printable parts and CAD sources), `firmware/` (when it has its
own code) and `images/`.

| JIM | Scopum | Micro Raider |
| ------------- | ------------- | ------------- |
| <img src="JIM/images/jim.jpg" height="250" align="center"> | <img src="Scopum/images/scopum.png" height="250" align="center"> | <img src="MicroRaider/images/microraider.jpg" height="250" align="center"> |
| By [Sonia Verdú](http://www.soniaverdu.es/) | By [Macarena González](https://github.com/MacarenaGB)| By  [Javier Isabel](https://github.com/JavierIH)|

| Forge | Zowiquilator | Kobuki |
| ------------- | ------------- | ------------- |
|<img src="Forge/images/forge.jpg" height="250" align="center"> | <img src="Zowiquilator/images/zowiquilator.jpg" height="250" align="center"> | <img src="Kobuki/images/kobuki.jpg" height="250" align="center"> |
| By [David Sánchez](https://github.com/davidsanfal) | by [Alberto Arribas](http://www.albertoarribasart.com/)  | By [Sonia Verdú](http://www.soniaverdu.es/) |

| Zowimanoid (template)| IronZowi | Zowarrior |
| ------------- | ------------- | ------------- |
| <img src="Zowimanoid/images/zowimanoid.png" height="250" align="center"> |<img src="IronZowi/images/home.jpg" height="250" align="center"> | (no picture yet) |
| By  [Javier Isabel](https://github.com/JavierIH) | By  [Gianluca Pugliese](https://github.com/owenlab) | |

## Firmware

The mods with a `firmware/platformio.ini` (Forge, IronZowi, Kobuki, MicroRaider, Zowiquilator) use the
Oscillator library from the ArduSnake submodule in [firmware/external](../firmware/external) (run
`git submodule update --init` first):

```
cd mods/Forge/firmware
pio run -t upload
```

Scopum keeps its own sketches for the Arduino IDE in `Scopum/firmware/`, and its Protocoder remote control in
`Scopum/protocoder/`.
