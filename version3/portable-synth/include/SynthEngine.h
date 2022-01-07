#pragma once

#include <Audio.h>
#include "AudioConstants.h"

class SynthEngine
{
public:
    virtual void noteOn(int note, int velocity);
    virtual void noteOff();
    virtual AudioMixer4 *getOutput();
};


class SynthManager
{
public:
    virtual SynthEngine* getEngine(int i);
};