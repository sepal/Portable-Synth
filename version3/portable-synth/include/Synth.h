#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "Input.h"
#include "AudioConstants.h"
#include "SynthEngine.h"
#include "VoiceGroup.h"

class Synth : public KeyboardHandler
{
public:
    Synth(SynthManager* initialSynth);

    void keyboardEvent(int button, bool pressed);

protected:
    int octave;

    SynthManager* synth;
    VoiceGroup* voices;
    AudioOutputI2S* i2s1;
    AudioMixer4* outputMixer;
    AudioConnection* voicesCord;
    AudioConnection* patchCord1;
    AudioConnection* patchCord2;
};