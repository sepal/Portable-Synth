#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "Input.h"
#include "AudioConstants.h"
#include "VoiceGroup.h"

class WaveFormSynth : public KeyboardHandler
{
public:
    WaveFormSynth();

    void keyboardEvent(int button, bool pressed);

protected:
    int octave;

    VoiceGroup voices;
    AudioOutputI2S i2s1;
    AudioMixer4 outputMixer;
    AudioConnection *patchCord1;
    AudioConnection *patchCord2;
};