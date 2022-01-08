#include <Arduino.h>
#include <Wire.h>
#include <Audio.h>

#include "Input.h"
#include "Synth.h"
#include "WaveformSynthEngine.h"
#include "FMSynthEngine.h"

Input input;

WaveFormSynthManager* waveformSynth;
FMSynthManager* fmSynth;
Synth *synth;

AudioOutputI2S* i2s1;
AudioMixer4* output;
AudioConnection* voicesCord;
AudioConnection* cords[3];
AudioControlSGTL5000* codec;


void setup()
{
    Serial.begin(9600);
    waveformSynth = new WaveFormSynthManager();
    fmSynth = new FMSynthManager();
    synth = new Synth(fmSynth);

    output = new AudioMixer4();
    i2s1 = new AudioOutputI2S();

    cords[0] = new AudioConnection(*synth->getOutput(), 0, *output, 0);
    cords[1] = new AudioConnection(*output, 0, *i2s1, 0);
    cords[2] = new AudioConnection(*output, 0, *i2s1, 1);
    


    codec = new AudioControlSGTL5000();
    codec->enable();
    codec->volume(0.2); // caution: very loud - use oscilloscope only!
    codec->dacVolumeRamp();
    codec->lineOutLevel(13);
    codec->volume(0.45);
    
    input.begin();
    input.setKeyboardHandler(synth);
    input.setMenuButtonHandler(synth);
    input.setEncoderHandler(fmSynth);




    //Give Audio Library a lot of memory to work with
    AudioMemory(24);
    AudioInterrupts();
}

void loop()
{
    input.update();
}