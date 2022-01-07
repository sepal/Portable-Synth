#include "Synth.h"

Synth::Synth(SynthManager* initialSynth)
{
    this->octave = 4;
    this->synth = initialSynth;

    this->voices = new VoiceGroup(this->synth);
    this->outputMixer = new AudioMixer4();
    this->i2s1 = new AudioOutputI2S();
    
    this->voicesCord = new AudioConnection(*this->voices->getOutput(), 0, *this->outputMixer, 0);
    this->patchCord1 = new AudioConnection(*this->outputMixer, 0, *i2s1, 0);
    this->patchCord2 = new AudioConnection(*this->outputMixer, 0, *i2s1, 1);
}

void Synth::keyboardEvent(int button, bool pressed)
{
    int n = octave * 12 + button;
    AudioNoInterrupts();
    if (pressed)
    {
        this->voices->noteOn(n, 127);
    }
    else
    {
        this->voices->noteOff(n);
    }
    AudioInterrupts();
}