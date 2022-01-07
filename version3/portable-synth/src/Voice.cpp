#include "Voice.h"

Voice::Voice()
{
    // this->engine = new BadAssSynthEngine();
}

void Voice::noteOn(int note, int velocity)
{

    this->engine.noteOn(note, velocity);
    this->isNoteOn = true;
    this->currentNote = note;
}

void Voice::noteOff()
{
    this->engine.noteOff();
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

void Voice::connect(AudioStream &destination, int channel)
{
    this->engine.connect(destination, channel);
}