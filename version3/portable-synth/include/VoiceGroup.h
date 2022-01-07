#pragma once

#include <Audio.h>
#include "Voice.h"
#include "SynthEngine.h"

#define MAX_VOICES 8


class VoiceGroup
{
public:
    VoiceGroup();

    void noteOn(int note, int velocity);
    void noteOff(int note);

    AudioMixer4* getOutput();
protected:
    Voice* voices[MAX_VOICES];
    AudioMixer4* mixers[MAX_VOICES/4];
    AudioConnection* cords[MAX_VOICES];
    AudioConnection* outputCord;
    AudioMixer4* output;
};

