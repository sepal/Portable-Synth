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
        // AM and Ring
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
        this->sineModulator->frequency(freq);
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

private:
    AudioSynthWaveformModulated *sineFM;
    AudioSynthWaveformModulated *sawtoothFM;
    AudioSynthWaveformSine *sineModulator;
    AudioMixer4 *mixer;
    AudioEffectEnvelope *envelope;
    AudioConnection *patchCords[7];
    AudioMixer4 *output;
};


class FMSynthManager: public EncoderHandler, public SynthManager
{
public:
    FMSynthManager()
    {
        for (int i=0; i < SYNTH_MAX_VOICES; i++)
        {
            this->engines[i] = new FMSynthEngine();
        }
    }

    virtual void encoderEvent(int encoder, int pos, bool moved_left)
    {

    }

    virtual SynthEngine* getEngine(int i) {
        return this->engines[i];
    }

private:
    FMSynthEngine* engines[SYNTH_MAX_VOICES];
};