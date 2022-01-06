#include <Arduino.h>
#include <Wire.h>
#include <Audio.h>

#include "Input.h"
#include "WaveFormSynth.h"

AudioControlSGTL5000 codec;

Input input;
WaveFormSynth synth;

void setup()
{
    Serial.begin(9600);
    input.begin();
    input.setKeyboardHandler(&synth);

    codec.enable();
    codec.volume(0.2); // caution: very loud - use oscilloscope only!
    codec.dacVolumeRamp();
    codec.lineOutLevel(13);
    codec.volume(0.45);


    //Give Audio Library a lot of memory to work with
    AudioMemory(24);
    AudioInterrupts();
}

void loop()
{
    input.update();
}