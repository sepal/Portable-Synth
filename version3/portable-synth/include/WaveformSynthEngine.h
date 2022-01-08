#pragma once

#include <Audio.h>
#include "AudioConstants.h"
#include "InputHandler.h"
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

    void setAttack(float attack) {
        this->env->attack(attack);
    }

    void setDecay(float attack) {
        this->env->decay(attack);
    }

    void setSustain(float level) {
        this->env->sustain(level);
    }

    void setRelease(float release) {
        this->env->release(release);
    }

protected:
    AudioSynthWaveform *osc[2];
    AudioMixer4 *oscMixer;
    AudioEffectEnvelope *env;
    AudioFilterStateVariable *filter;
    AudioMixer4 *output;
    AudioConnection *cords[6];
};

class WaveFormSynthManager : public EncoderHandler, public SynthManager
{
public:
    WaveFormSynthManager()
    {
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i] = new WaveFormSynthEngine();
            this->engines[i]->setFilterParams(freq, q);
        }

        page = PAGE_FILTER;
    }

    virtual void encoderEvent(int encoder, bool moved_left)
    {
        switch (this->page)
        {
        case PAGE_FILTER:
            handleFilterPageEncoder(encoder, moved_left);
            break;
        
        case PAGE_ADSR:
            handleADSRPageEncoder(encoder, moved_left);
            break;
        }
    }

    virtual void nextPage()
    {
        switch (this->page)
        {
        case PAGE_FILTER:
            Serial.println("ADSR settings");
            this->page = PAGE_ADSR;
            break;
        case PAGE_ADSR:
            Serial.println("Filter settings");
            this->page = PAGE_FILTER;
            break;
        }
    }

    virtual void prevPage()
    {
        switch (this->page)
        {
        case PAGE_FILTER:
            Serial.println("ADSR settings");
            this->page = PAGE_ADSR;
            break;
        case PAGE_ADSR:
            Serial.println("Filter settings");
            this->page = PAGE_FILTER;
            break;
        }
    }

    void handleFilterPageEncoder(int encoder, bool moved_left)
    {
        switch (encoder)
        {
        case 0:
            freq += moved_left ? -100 : 100;
            if (freq > 10000)
                freq = 10000;
            if (freq < 20)
                freq = 20;
            break;
        case 1:
            q += moved_left ? -0.1f : 0.1f;
            if (q > 5.0)
                q = 5.0;
            if (q < 0.7)
                q = 0.7;
            break;
        }

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setFilterParams(freq, q);
        }
        AudioInterrupts();
    }

    void handleADSRPageEncoder(int encoder, bool moved_left)
    {
        switch(encoder)
        {
        case 0:
            this->attack += moved_left ? -0.1 : 1;
            this->setAttack(attack);
            Serial.println(attack);
            break;
        case 1:
            this->decay += moved_left ? -1 : 1;
            this->setDecay(decay);
            Serial.println(decay);
            break;
        case 2:
            this->sustain += moved_left ? -0.01f : 0.01f;
            this->setSustain(sustain);
            Serial.println(sustain);
            break;
        case 3:
            this->release += moved_left ? -1 : 1;
            this->setRelease(release);
            Serial.println(release);
            break;
        }
    }

    void setAttack(float attack)
    {

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setAttack(attack);
        }
        AudioInterrupts();
    }

    void setDecay(float decay)
    {

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setDecay(decay);
        }
        AudioInterrupts();
    }

    void setSustain(float sustain)
    {

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setSustain(sustain);
        }
        AudioInterrupts();
    }

    void setRelease(float release)
    {

        AudioNoInterrupts();
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i]->setRelease(release);
        }
        AudioInterrupts();
    }

    virtual SynthEngine *getEngine(int i)
    {
        return this->engines[i];
    }

protected:
    enum SettingsPage
    {
        PAGE_FILTER,
        PAGE_ADSR
    };

    WaveFormSynthEngine *engines[SYNTH_MAX_VOICES];

    SettingsPage page;

    int freq = 1000;
    float q = 1.0f;

    float attack = 10.0f;
    float decay = 35.0f;
    float sustain = 0.5f;
    float release = 300.0f;
};