#include "VoiceGroup.h"

VoiceGroup::VoiceGroup(SynthManager* synth)
{
    for (int i=0; i<SYNTH_MAX_VOICES; i++)
    {
        this->voices[i] = new Voice(synth->getEngine(i));
    }

        Serial.println("Init mixers");
    this->mixers[0] = new AudioMixer4();
    this->mixers[1] = new AudioMixer4();


    this->output = new AudioMixer4();


    this->cords[0] = new AudioConnection(*this->voices[0]->getOutput(), 0, *this->mixers[0], 1);
    this->cords[1] = new AudioConnection(*this->voices[1]->getOutput(), 0, *this->mixers[0], 2);
    this->cords[2] = new AudioConnection(*this->voices[2]->getOutput(), 0, *this->mixers[0], 3);
    this->cords[3] = new AudioConnection(*this->voices[3]->getOutput(), 0, *this->mixers[0], 4);
    this->cords[4] = new AudioConnection(*this->voices[4]->getOutput(), 0, *this->mixers[1], 1);
    this->cords[5] = new AudioConnection(*this->voices[5]->getOutput(), 0, *this->mixers[1], 2);
    this->cords[6] = new AudioConnection(*this->voices[6]->getOutput(), 0, *this->mixers[1], 3);
    this->cords[7] = new AudioConnection(*this->voices[7]->getOutput(), 0, *this->mixers[1], 4);

    this->outputCord = new AudioConnection(*this->mixers[0], 0, *this->output, 0);
    this->outputCord = new AudioConnection(*this->mixers[1], 0, *this->output, 1);

    this->mixers[0]->gain(0, 0.25);
    this->mixers[0]->gain(1, 0.25);
    this->mixers[0]->gain(2, 0.25);
    this->mixers[0]->gain(3, 0.25);

    this->mixers[1]->gain(0, 0.25);
    this->mixers[1]->gain(1, 0.25);
    this->mixers[1]->gain(2, 0.25);
    this->mixers[1]->gain(3, 0.25);

    this->output->gain(0, 0.5);
    this->output->gain(1, 0.5);
}

void VoiceGroup::noteOn(int note, int velocity)
{
    for (int i = 0; i < SYNTH_MAX_VOICES; i++)
    {
        if (!this->voices[i]->isPlaying())
        {
            this->voices[i]->noteOn(note, velocity);
            return;
        }
    }
}

void VoiceGroup::noteOff(int note)
{
    for (int i = 0; i < SYNTH_MAX_VOICES; i++)
    {
        if (this->voices[i]->isPlaying() && this->voices[i]->note() == note)
        {
            this->voices[i]->noteOff();
        }
    }
}

AudioMixer4* VoiceGroup::getOutput()
{
    return this->output;
}

void forwardEncoderEvent() {
    for (int i = 0; i < SYNTH_MAX_VOICES; i++)
    {
        
    }
}