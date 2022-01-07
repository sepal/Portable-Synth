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

    void connect(AudioStream &destination, int channel);

protected:
    FMSynthEngine engine;
    int currentNote;
    bool isNoteOn;
};