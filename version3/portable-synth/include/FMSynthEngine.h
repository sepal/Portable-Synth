#pragma once

#include <Audio.h>
#include "SynthEngine.h"
#include "Input.h"

/**
 * SynthEngine based on https://github.com/ghostintranslation/synth.
 */
class FMSynthEngine : public SynthEngine
{
public:
    FMSynthEngine()
    {
        this->sineFM = new AudioSynthWaveformModulated();
        this->sineFM->amplitude(1);
        this->sawtoothFM = new AudioSynthWaveformModulated();
        this->sawtoothFM->begin(WAVEFORM_SAWTOOTH);
        this->sawtoothFM->amplitude(1);
        this->mixer = new AudioMixer4();
        this->mixer->gain(0, 0.3);
        this->mixer->gain(1, 0.2);
        this->sineModulator = new AudioSynthWaveformSine();
        this->envelope = new AudioEffectEnvelope();
        this->envelope->sustain(1);
        this->output = new AudioMixer4();
        this->output->gain(1, 0);
        this->output->gain(0, 1);

        this->patchCords[0] = new AudioConnection(*this->sineModulator, 0, *this->sawtoothFM, 0);
        this->patchCords[1] = new AudioConnection(*this->sineModulator, 0, *this->sineFM, 0);
        this->patchCords[2] = new AudioConnection(*this->sineFM, 0, *this->mixer, 0);
        this->patchCords[3] = new AudioConnection(*this->sawtoothFM, 0, *this->mixer, 1);
        this->patchCords[4] = new AudioConnection(*this->mixer, 0, *this->envelope, 0);
        this->patchCords[5] = new AudioConnection(*this->envelope, 0, *this->output, 0);
        this->patchCords[6] = new AudioConnection(*this->mixer, 0, *this->output, 1);
    }

    virtual void noteOn(int note, int velocity)
    {

        float freq = NOTE_FREQ[note];
        Serial.println(note);
        this->sawtoothFM->frequency(freq);
        this->sineFM->frequency(freq);
        this->envelope->noteOn();
    }

    virtual void noteOff()
    {
        this->envelope->noteOff();
    }

    AudioMixer4 *getOutput()
    {
        return this->output;
    }

    inline void setModulatorFrequency(int freq)
    {
        this->sineModulator->frequency(freq);
    }

    inline void setModulatorAmplitude(float amp)
    {
        this->sineModulator->amplitude(amp);
    }

    void setShape(float shape)
    {
        this->mixer->gain(0, (1 - shape) * 0.3);
        this->mixer->gain(1, shape * 0.2);
    }

private:
    AudioSynthWaveformModulated *sineFM;
    AudioSynthWaveformModulated *sawtoothFM;
    AudioSynthWaveformSine *sineModulator;
    AudioMixer4 *mixer;
    AudioEffectEnvelope *envelope;
    AudioConnection *patchCords[7];
    AudioMixer4 *output;
};

class FMSynthManager : public EncoderHandler, public SynthManager
{
public:
    FMSynthManager()
    {
        for (int i = 0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i] = new FMSynthEngine();
        }

        this->setModulatorFrequency(modFreq);
        this->setModulatorAmplitude(modAmp);
    }

    virtual void encoderEvent(int encoder, bool moved_left)
    {
        switch (encoder)
        {
        case 0:
            modFreq += (moved_left) ? -1 : 1;
            if (modFreq > 1000) modFreq = 1000;
            if (modFreq < 0) modFreq = 0;
            this->setModulatorFrequency(modFreq);
            break;

        case 1:
            modAmp += (moved_left) ? -0.001 : 0.001;
            if (modAmp > 0.5f) modAmp = 0.5f;
            if (modAmp < 0.0f) modAmp = 0.0f;
            AudioNoInterrupts();
            this->setModulatorAmplitude(modAmp);
            break;
        }
    }

    virtual SynthEngine *getEngine(int i)
    {
        return this->engines[i];
    }

    void setModulatorFrequency(float modFreq) {
        Serial.print("Mod freq: ");
        Serial.println(modFreq);
        AudioNoInterrupts();
        for (int i=0; i<SYNTH_MAX_VOICES; i++) {
            this->engines[i]->setModulatorFrequency(modFreq);
            AudioInterrupts();
        }
    }

    void setModulatorAmplitude(float modFreq) {
        Serial.print("Mod amp: ");
        Serial.println(modAmp);
        AudioNoInterrupts();
        for (int i=0; i<SYNTH_MAX_VOICES; i++) {
            this->engines[i]->setModulatorAmplitude(modFreq);
        }
        AudioInterrupts();
    }


private:
    FMSynthEngine *engines[SYNTH_MAX_VOICES];

    float modFreq = 0;
    float modAmp = 0;
};