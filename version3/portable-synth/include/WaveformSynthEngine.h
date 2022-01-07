#pragma once

#include <Audio.h>
#include "SynthEngine.h"


class WaveFormSynthEngine : public SynthEngine
{
public:
    WaveFormSynthEngine()
    {
        osc[0] = new AudioSynthWaveform();
        osc[1] = new AudioSynthWaveform();

        oscMixer = new AudioMixer4();

        this->env = new AudioEffectEnvelope();
        this->filter = new AudioFilterBiquad();

        this->output = new AudioMixer4();

        for (int i=0; i<2; i++) {
            cords[0] = new AudioConnection(*osc[i], 0, *oscMixer, 0);
            oscMixer->gain(i, 0.5); 
            
        }

        cords[2] = new AudioConnection(*oscMixer, *env);
        cords[4] = new AudioConnection(*env, *filter);
        cords[5] = new AudioConnection(*filter, 0, *output, 0);

        osc[0]->begin(WAVEFORM_SAWTOOTH); 
        osc[1]->begin(WAVEFORM_SQUARE);
        osc[0]->amplitude(1);
        osc[1]->amplitude(1);
        filter->setLowpass(0, 1000, 1.0);
    }
    

    virtual void noteOn(int note, int velocity)
    {
        for (int i=0; i<3; i++) {
            this->osc[i]->frequency(NOTE_FREQ[note]);
        }
        this->env->noteOn();
    }

    virtual void noteOff()
    {
        this->env->noteOff();
    }

    virtual AudioMixer4 *getOutput()
    {
        return this->output;
    }

protected:
    AudioSynthWaveform* osc[2];
    AudioMixer4* oscMixer;
    AudioEffectEnvelope* env;
    AudioFilterBiquad* filter;
    AudioMixer4* output;
    AudioConnection* cords[6];
};