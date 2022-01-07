#pragma once

#include <Audio.h>
#include "AudioConstants.h"
#include "Input.h"
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
        this->filter = new AudioFilterStateVariable();

        this->output = new AudioMixer4();

        for (int i = 0; i < 2; i++)
        {
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
        filter->frequency(1000);
        filter->resonance(1.0);
    }

    virtual void noteOn(int note, int velocity)
    {
        this->osc[0]->frequency(NOTE_FREQ[note]);
        this->osc[1]->frequency(NOTE_FREQ[note]);
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

    void setFilterParams(int freq, int q)
    {
        this->filter->frequency(freq);
        this->filter->resonance(q);
    }

protected:
    AudioSynthWaveform *osc[2];
    AudioMixer4 *oscMixer;
    AudioEffectEnvelope *env;
    AudioFilterStateVariable *filter;
    AudioMixer4 *output;
    AudioConnection *cords[6];
};

class WaveFormSynthManager: public EncoderHandler, public SynthManager
{
public:
    WaveFormSynthManager()
    {
        for (int i=0; i < SYNTH_MAX_VOICES; i++) {
            this->engines[i] = new WaveFormSynthEngine();
            this->engines[i]->setFilterParams(freq, q);
        }
    }

    virtual void encoderEvent(int encoder, bool moved_left)
    {
        switch (encoder)
        {
        case 0:
            freq += moved_left ? -100 : 100;
            if (freq > 10000) freq = 10000; 
            if (freq < 20) freq = 20;
            break;
        case 1:
            q += moved_left ? -0.1f : 0.1f;
            if (q > 5.0) q = 5.0; 
            if (q < 0.7) q = 0.7;
            break;
    
        }
        Serial.print(freq);
        Serial.print(" ");
        Serial.println(q);

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setFilterParams(freq, q);
        }
        AudioInterrupts();
        
    }


    virtual SynthEngine* getEngine(int i) {
        return this->engines[i];
    }

protected:
    WaveFormSynthEngine* engines[SYNTH_MAX_VOICES];

    int freq = 1000;
    float q = 1.0f;
};