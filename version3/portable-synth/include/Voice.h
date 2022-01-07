#pragma once

#include <Audio.h>
#include "AudioConstants.h"

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
    AudioSynthWaveform waveform1;
    AudioConnection* patchCord;
    int currentNote;
    bool isNoteOn;
};