#include "Synth.h"

Synth::Synth(SynthManager *initialSynth)
{
    this->octave = 4;
    this->synth = initialSynth;

    this->voices = new VoiceGroup(this->synth);
    this->output = new AudioMixer4();

    this->cords[0] = new AudioConnection(*this->voices->getOutput(), 0, *this->output, 0);
}

void Synth::keyboardEvent(int button, bool pressed)
{
    int n = octave * 12 + button;
    AudioNoInterrupts();
    if (pressed)
    {
        this->voices->noteOn(n, 127);
    }
    else
    {
        this->voices->noteOff(n);
    }
    AudioInterrupts();
}

void Synth::menuButtonEvent(MenuButtonHandler::BUTTONS button, bool pressed)
{
    if (pressed)
    {
        switch (button)
        {
        case MenuButtonHandler::LEFT:
            this->synth->prevPage();
            break;
        case MenuButtonHandler::RIGHT:
            this->synth->nextPage();
            break;
        case MenuButtonHandler::MAIN:
            break;
        }
    }
}

AudioMixer4 *Synth::getOutput()
{
    return this->output;
}