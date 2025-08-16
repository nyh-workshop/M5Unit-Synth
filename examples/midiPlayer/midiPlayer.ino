#include <LittleFS.h>
#include <MD_MIDIFile.h>
#include <M5UnitSynth.h>

M5UnitSynth synth;
MD_MIDIFile SMF;

void midiCallback(midi_event *pev)
// Called by the MIDIFile library when a file event needs to be processed
// thru the midi communications interface.
// This callback is set up in the setup() function.
{
  // Define constants for MIDI channel voice message IDs
  const uint8_t NOTE_OFF = 0x80;  // note on
  const uint8_t NOTE_ON = 0x90;   // note off. NOTE_ON with velocity 0 is same as NOTE_OFF

  switch (pev->data[0]) {
    case NOTE_OFF:  // [1]=note no, [2]=velocity
      // playNote(pev->data[1], SILENT);
      synth.setNoteOff(0, pev->data[1], pev->data[2]); 
      Serial.printf("NOTE_OFF ch: %d\n", pev->data[1]);
      break;

    case NOTE_ON:  // [1]=note_no, [2]=velocity
      // Note ON with velocity 0 is the same as off
      // playNote(pev->data[1], (pev->data[2] == 0) ? SILENT : ACTIVE);
      // Velocity is not included for now!
      synth.setNoteOn(0, pev->data[1], pev->data[2]);
      Serial.printf("NOTE_ON trk: %d, ch: %d, no: %d\n", pev->track, pev->channel, pev->data[1]);
      break;

    default:
      break;
  }
}

static enum { S_IDLE, S_PLAYING } state = S_IDLE;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello M5 Unit Synth :D");
  synth.begin(&Serial2, UNIT_SYNTH_BAUD, 5, 4);
  synth.setInstrument(0, 0, GrandPiano_1);

  // Initialize LittleFS:
  if (!LittleFS.begin()) {
    Serial.println("LittleFS init fail!");
    while (1)
      ;
  }

  // Initialize MIDIFile:
  SMF.begin(&LittleFS);
  SMF.setMidiHandler(midiCallback);

  Serial.println("Start playing song now!");

  // Load a MIDI file from there:
  int err = SMF.load("merryChristmas.mid");

  if (err != MD_MIDIFile::E_OK) {
    Serial.printf("SMF load error: %d", err);
    while (1)
      ;
  }

  Serial.printf("Filename: %s\n", SMF.getFilename());
  Serial.printf("Format: %d\n", SMF.getFormat());

  state = S_PLAYING;
}

void loop() {
  switch (state) {
    case S_IDLE:
      delay(500);
      break;
    case S_PLAYING:
      if (!SMF.isEOF()) {
        SMF.getNextEvent();
      } else {
        Serial.println("Playing done! Idle mode now...");
        state = S_IDLE;
      }
      break;
    default:
      break;
  }
}