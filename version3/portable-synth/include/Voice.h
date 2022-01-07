#pragma once

#include <Audio.h>
#include "AudioConstants.h"

#include "SynthEngine.h"
#include "FMSynthEngine.h"
#include "WaveformSynthEngine.h"

class Voice
{
public:
    Voice();
    void noteOn(int note, int velocity);
    void noteOff();

    int note();
    bool isPlaying();

    AudioMixer4 *getOutput();

protected:
    SynthEngine* engine;
    int currentNote;
    bool isNoteOn;
};