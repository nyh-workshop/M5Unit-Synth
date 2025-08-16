# M5Unit-Synth

## Overview

Contains case programs of M5Stack Unit Synth.

Added compatibility for Raspberry Pico RP2040 and RP2350.

Additional example: `midiPlayer`

## To use the Midi Player:
- Raspberry Pi RP2040/RP2350 board library (4.1.1)

- Get the Modified MajicDesigns' [MD_MIDIFile](https://github.com/nyh-workshop/MD_MIDIFile) library to play MIDI files from LittleFS (Flash size: 128KB)

- [arduino-littlefs-upload extension](https://github.com/earlephilhower/arduino-littlefs-upload) for uploading the midi files into the flash.

## Connecting the M5Unit-Synth to the Raspberry Pico:
- This uses the `UART1` by default, so connect the Pico's `GP4` (TX) to the Synth's `IN` (yellow) pin.

## Installation and usage instructions for the Midi Player:
- Unzip the [MIDI parser](https://github.com/nyh-workshop/MD_MIDIFile) into the Arduino's `Documents\Arduino\Libraries` folder.
- Install the [arduino-littlefs-upload extension](https://github.com/earlephilhower/arduino-littlefs-upload) into the `C:\Users\<username>\.arduinoIDE\plugins\`.
- At the `Tools->Flash Size` select `Sketch:3968KB,FS:128KB` before compiling.
- A sample midi file is there inside for testing.

## Notes:
- If the M5 Unit Synth is connected to a +3V3 supply rather than the +5V supply, it could be a less louder.

## License

[Unit Synth - MIT](LICENSE)

