#pragma once

#include <Audio.h>
#include "SynthEngine.h"


class WaveFormSynthEngine : public SynthEngine
{
public:
    WaveFormSynthEngine()
    {
        for (int i=0; i<2; i++) {
            cords[0] = new AudioConnection(osc[i], 0, oscMixer, 0);
            oscMixer.gain(i, 0.333); 
            
        }
        cords[3] = new AudioConnection(oscMixer, env);
        cords[4] = new AudioConnection(env, amp);
        cords[5] = new AudioConnection(amp, filter);

        osc[0].begin(WAVEFORM_SAWTOOTH); 
        osc[1].begin(WAVEFORM_SQUARE);
        osc[0].amplitude(1);
        osc[1].amplitude(1);
        filter.setLowpass(0, 1000, 1.0);
    }
    

    virtual void noteOn(int note, int velocity)
    {
        for (int i=0; i<3; i++) {
            this->osc[i].frequency(NOTE_FREQ[note]);
        }
        this->env.noteOn();
    }

    virtual void noteOff()
    {
        this->env.noteOff();
    }

    virtual void connect(AudioStream &destination, int channel)
    {
        delete this->output;

        this->output = new AudioConnection(this->filter, 0, destination, channel);
    }

protected:
    AudioSynthWaveform osc[2];
    AudioMixer4 oscMixer;
    AudioEffectEnvelope env;
    AudioAmplifier amp;
    AudioFilterBiquad filter;
    AudioConnection* cords[6];
    AudioConnection* output;
};