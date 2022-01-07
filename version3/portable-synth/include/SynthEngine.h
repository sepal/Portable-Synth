#pragma once

#include <Audio.h>
#include "AudioConstants.h"

class SynthEngine
{
public:
    virtual void noteOn(int note, int velocity);
    virtual void noteOff();
    virtual void connect(AudioStream &destination, int channel);
};
