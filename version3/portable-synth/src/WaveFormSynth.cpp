#include "WaveFormSynth.h"

WaveFormSynth::WaveFormSynth()
{
    this->octave = 4;
    this->voices.connect(this->outputMixer, 0);
    this->patchCord1 = new AudioConnection(this->outputMixer, 0, i2s1, 0);
    this->patchCord2 = new AudioConnection(this->outputMixer, 0, i2s1, 1);
}

void WaveFormSynth::keyboardEvent(int button, bool pressed)
{
    int n = octave * 12 + button;
    AudioNoInterrupts();
    if (pressed)
    {
        this->voices.noteOn(n, 127);
    }
    else
    {
        this->voices.noteOff(n);
    }
    AudioInterrupts();
}