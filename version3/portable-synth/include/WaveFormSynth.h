#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "Input.h"
#include "AudioConstants.h"

class WaveFormSynth : public KeyboardHandler
{
public:
    WaveFormSynth();

    void keyboardEvent(int button, bool pressed);
    

protected:
    int octave;


    AudioSynthWaveform    waveform1;
    AudioOutputI2S        i2s1;
    AudioConnection       patchCord1;
    AudioConnection       patchCord2;
    AudioControlSGTL5000 codec;
};