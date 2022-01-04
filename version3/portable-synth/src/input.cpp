#include "Input.h"

#include <Wire.h>

void Input::begin()
{
    Wire.begin();
}

void Input::update()
{
    this->readData();

    // Check updates on menu buttons
    for (int i = 0; i < 3; i++)
    {
        if (bitRead(buttonStates[5], Input::MENU_BIT_MAPPIN[i]) != bitRead(lastButtonStates[5], Input::MENU_BIT_MAPPIN[i]))
        {
            updateMenu(i, bitRead(buttonStates[5], Input::MENU_BIT_MAPPIN[i]));
        }
    }

    // Check keyboard updates.
    for (int i = KEYBOARD_FIRST; i <= KEYBOARD_LAST; i++)
    {
        if (bitRead(buttonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]) != bitRead(lastButtonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]))
        {
            updateKeyboard(i, bitRead(buttonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]));
        }
    }

    // Update pads.
    for (int i = 0; i < 12; i++)
    {
        if (bitRead(buttonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]) != bitRead(lastButtonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]))
        {
            updatePad(i, bitRead(buttonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]));
        }
    }

    // Update utility buttons.
    for (int i = 0; i < 8; i++)
    {
        if (bitRead(buttonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]) != bitRead(lastButtonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]))
        {
            updateUtility(i, bitRead(buttonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]));
        }
    }

    // Update encoder buttons.
    for (int i = 0; i < 4; i++)
    {
        if (bitRead(buttonStates[6], ENCODER_BIT_MAPPING[i]) != bitRead(lastButtonStates[6], ENCODER_BIT_MAPPING[i]))
        {
            updateEncoderButton(i, bitRead(buttonStates[6], ENCODER_BIT_MAPPING[i]));
        }
    }

    // Update encoders.
    if (lastButtonStates[7] != buttonStates[7]) {
        for (int i = 0; i < 4; i++){
            byte mask = B00000011;
            mask = mask << i*2;
            byte enc_val = buttonStates[7] & mask;
            enc_val = enc_val >> i*2;
            if (enc_val == 2){
                encoders[i]--;
            }
            else if (enc_val == 1){
                encoders[i]++;
            }
            updateEncoder(i, encoders[i], enc_val == 2);
        }
    }
}


void Input::readData()
{
    Wire.requestFrom(9, 8);
    lastButtonStates[0] = buttonStates[0];
    lastButtonStates[1] = buttonStates[1];
    lastButtonStates[2] = buttonStates[2];
    lastButtonStates[3] = buttonStates[3];
    lastButtonStates[4] = buttonStates[4];
    lastButtonStates[5] = buttonStates[5];
    lastButtonStates[6] = buttonStates[6];
    lastButtonStates[7] = buttonStates[7];

    while (Wire.available())
    {

        buttonStates[0] = Wire.read();
        buttonStates[1] = Wire.read();
        buttonStates[2] = Wire.read();
        buttonStates[3] = Wire.read();
        buttonStates[4] = Wire.read();
        buttonStates[5] = Wire.read();
        buttonStates[6] = Wire.read();
        buttonStates[7] = Wire.read();
    }
}

void Input::updateMenu(MENU_BUTTONS button, bool pressed)
{
    switch (button)
    {
    case Input::MENU_MAIN:
        Serial.print("Main menu: ");
        Serial.println(pressed, DEC);
        break;
    case Input::MENU_LEFT:
        Serial.print("Left menu: ");
        Serial.println(pressed, DEC);
        break;
    case Input::MENU_RIGHT:
        Serial.print("Right menu: ");
        Serial.println(pressed, DEC);
        break;
    }
}

void Input::updateKeyboard(KEYBOARD_BUTTONS button, bool pressed)
{
    if (pressed)
    {
        Serial.print("Keyboard pressed ");
        Serial.println(button, DEC);
    }
}

void Input::updatePad(int pad, bool pressed)
{
    if (pressed)
    {
        Serial.print("Pad pressed ");
        Serial.println(pad, DEC);
    }
}

void Input::updateUtility(int key, bool pressed)
{
    if (pressed)
    {
        Serial.print("Utility pressed ");
        Serial.println(key, DEC);
    }
}

void Input::updateEncoderButton(int encoder, bool pressed) {
    if (pressed)
    {
        Serial.print("Encoder pressed ");
        Serial.println(encoder, DEC);
    }
}

void Input::updateEncoder(int encoder, int pos, bool moved_left) {
    Serial.print("Encoder ");
    Serial.print(encoder, DEC);
    Serial.print(" moved to pos ");
    Serial.println(pos, DEC);
}