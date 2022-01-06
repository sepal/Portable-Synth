#include "WaveFormSynth.h"


WaveFormSynth::WaveFormSynth() : 
patchCord1(waveform1, 0, i2s1, 0),
patchCord2(waveform1, 0, i2s1, 1)
{
  waveform1.begin(WAVEFORM_SINE);
  this->octave = 4;
}


void WaveFormSynth::keyboardEvent(int button, bool pressed) {

    AudioNoInterrupts();
    if (pressed) {
        float f = NOTE_FREQ[octave * 12 + button];
        waveform1.frequency(f);
        waveform1.amplitude(1.0);
        Serial.println(f);
    }
    else {
        waveform1.amplitude(0.0);
    }
    AudioInterrupts();
}