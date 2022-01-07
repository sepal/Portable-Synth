#include "VoiceGroup.h"

VoiceGroup::VoiceGroup() {
    this->voices[0].connect(this->mixers[0], 0);
    this->voices[1].connect(this->mixers[0], 1);
    this->voices[2].connect(this->mixers[0], 2);
    this->voices[3].connect(this->mixers[0], 3);

    this->voices[0].connect(this->mixers[1], 0);
    this->voices[1].connect(this->mixers[1], 1);
    this->voices[2].connect(this->mixers[1], 2);
    this->voices[3].connect(this->mixers[1], 3);

    this->cords[0] = new AudioConnection(this->mixers[0], 0, this->output, 0);
    this->cords[1] = new AudioConnection(this->mixers[1], 0, this->output, 1);
    
    this->mixers[0].gain(0, 0.25);
    this->mixers[0].gain(1, 0.25);
    this->mixers[0].gain(2, 0.25);
    this->mixers[0].gain(3, 0.25);

    this->mixers[1].gain(0, 0.25);
    this->mixers[1].gain(1, 0.25);
    this->mixers[1].gain(2, 0.25);
    this->mixers[1].gain(3, 0.25);

    this->output.gain(0,0.5);
    this->output.gain(1,0.5);
}

void VoiceGroup::noteOn(int note, int velocity)
{
    for (int i = 0; i < MAX_VOICES; i++)
    {
        if (!this->voices[i].isPlaying()) {
            this->voices[i].noteOn(note, velocity);
            Serial.print("Note on voice ");
            Serial.println(i, DEC);
            return ;
        }
    }
}

void VoiceGroup::noteOff(int note)
{
    for (int i = 0; i < MAX_VOICES; i++)
    {
        if (this->voices[i].isPlaying() && this->voices[i].note() == note) {
            this->voices[i].noteOff();
            Serial.print("Note off voice ");
            Serial.println(i, DEC);
        }
    }
}

void VoiceGroup::connect(AudioStream &destination, int channel)
{
    delete this->patchCord;
    this->patchCord = new AudioConnection(this->output, 0, destination, channel);
}