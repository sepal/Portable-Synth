#pragma once

#include <Audio.h>
#include "AudioConstants.h"
#include "Voice.h"
#include "SynthEngine.h"

class VoiceGroup
{
public:
    VoiceGroup(SynthManager* synth);

    void noteOn(int note, int velocity);
    void noteOff(int note);

    AudioMixer4* getOutput();
protected:
    Voice* voices[SYNTH_MAX_VOICES];
    AudioMixer4* mixers[SYNTH_MAX_VOICES/4];
    AudioConnection* cords[SYNTH_MAX_VOICES];
    AudioConnection* outputCord;
    AudioMixer4* output;
};

