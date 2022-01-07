#include <Arduino.h>
#include <Wire.h>
#include <Audio.h>

#include "Input.h"
#include "Synth.h"
#include "WaveformSynthEngine.h"
#include "FMSynthEngine.h"

AudioControlSGTL5000 codec;

Input input;

WaveFormSynthManager* waveformSynth;
FMSynthManager* fmSynth;
Synth *synth;

void setup()
{
    Serial.begin(9600);
    waveformSynth = new WaveFormSynthManager();
    fmSynth = new FMSynthManager();
    synth = new Synth(fmSynth);

    codec.enable();
    codec.volume(0.2); // caution: very loud - use oscilloscope only!
    codec.dacVolumeRamp();
    codec.lineOutLevel(13);
    codec.volume(0.45);
    
    input.begin();
    input.setKeyboardHandler(synth);
    input.setEncoderHandler(fmSynth);


    //Give Audio Library a lot of memory to work with
    AudioMemory(24);
    AudioInterrupts();
}

void loop()
{
    AudioNoInterrupts();
    input.update();
    AudioInterrupts();
}