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

    AudioMixer4* getOutput();
protected:
    AudioConnection* cords[1];
    AudioMixer4* output;
    int octave;

    SynthManager* synth;
    VoiceGroup* voices;
};