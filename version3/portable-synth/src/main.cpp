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
Synth *synth;

void setup()
{
    Serial.begin(9600);
    waveformSynth = new WaveFormSynthManager();
    synth = new Synth(waveformSynth);

    codec.enable();
    codec.volume(0.2); // caution: very loud - use oscilloscope only!
    codec.dacVolumeRamp();
    codec.lineOutLevel(13);
    codec.volume(0.45);
    
    input.begin();
    input.setKeyboardHandler(synth);
    input.setEncoderHandler(waveformSynth);


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