#include "Voice.h"

Voice::Voice()
{
  waveform1.begin(WAVEFORM_SINE);
}

void Voice::noteOn(int note, int velocity) {
    this->waveform1.frequency(NOTE_FREQ[note]);
    this->waveform1.amplitude(VELOCITY_CURVES[0][velocity]);
    this->isNoteOn = true;
    this->currentNote = note;
}

void Voice::noteOff() {
    this->waveform1.amplitude(0);
    this->isNoteOn = false;
}

int Voice::note() {
    return this->currentNote;
}

bool Voice::isPlaying() {
    return this->isNoteOn;
}

void Voice::connect(AudioStream &destination, int channel) {
    delete this->patchCord;

    this->patchCord = new AudioConnection(this->waveform1, 0, destination, channel);
}