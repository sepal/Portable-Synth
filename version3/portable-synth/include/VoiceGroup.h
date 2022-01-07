#pragma once

#include <Audio.h>
#include "Voice.h"


#define MAX_VOICES 8


class VoiceGroup
{
public:
    VoiceGroup();

    void noteOn(int note, int velocity);
    void noteOff(int note);

    void connect(AudioStream &destination, int channel);
protected:
    Voice voices[MAX_VOICES];
    AudioMixer4 mixers[MAX_VOICES/4];
    AudioConnection *cords[MAX_VOICES/4];
    AudioConnection* patchCord = nullptr;
    AudioMixer4 output;
};

