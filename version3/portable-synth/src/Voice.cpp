#include "Voice.h"

Voice::Voice()
{
    engine = new WaveFormSynthEngine();
}

void Voice::noteOn(int note, int velocity)
{

    this->engine->noteOn(note, velocity);
    this->isNoteOn = true;
    this->currentNote = note;
}

void Voice::noteOff()
{
    this->engine->noteOff();
    this->isNoteOn = false;
}

int Voice::note()
{
    return this->currentNote;
}

bool Voice::isPlaying()
{
    return this->isNoteOn;
}

AudioMixer4* Voice::getOutput()
{
    return this->engine->getOutput();
}