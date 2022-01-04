#include <Arduino.h>
#include <Wire.h>

#include "Input.h"

Input input;

void setup() {
  Serial.begin(9600);
  input.begin();
}

void loop() {
  input.update();
}