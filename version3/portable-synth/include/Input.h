#pragma once

#include <Arduino.h>

class KeyboardHandler
{
public:
    virtual void keyboardEvent(int button, bool pressed);
};

class Input
{
public:
    void begin();

    void update();

    void setKeyboardHandler(KeyboardHandler* handler);

    enum MENU_BUTTONS
    {
        MENU_MAIN,
        MENU_LEFT,
        MENU_RIGHT,
    };

private:
    void readData();

    void updateKeyboard(int button, bool pressed);
    void updatePad(int pad, bool pressed);
    void updateMenu(MENU_BUTTONS button, bool pressed);
    void updateUtility(int key, bool pressed);
    void updateEncoderButton(int encoder, bool pressed);
    void updateEncoder(int encoder, int pos, bool moved_left);

    byte buttonStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    byte lastButtonStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int encoders[4] = {0, 0, 0, 0};

    const byte MENU_BIT_MAPPIN[3] = {5, 4, 6};

    KeyboardHandler* keyboardHandler;

    const byte KEYBOARD_BYTE_MAPPING[24] = {
        // SW:  25 18 26 19 27 28 20 36 21 37 29 38
        3,
        2,
        3,
        2,
        3,
        3,
        2,
        4,
        2,
        4,
        3,
        4,
        // SW:  39 30 40 31 41 42 32 35 33 43 34 44
        4,
        3,
        4,
        3,
        5,
        5,
        3,
        4,
        4,
        5,
        3,
        5,
    };

    const byte KEYBOARD_BIT_MAPPING[24] = {
        // SW:  25 18 26 19 27 28 20 36 21 37 29 38
        0,
        1,
        1,
        2,
        2,
        3,
        3,
        3,
        4,
        4,
        4,
        5,
        // SW:  39 30 40 31 41 42 32 35 33 43 34 44
        6,
        5,
        7,
        6,
        0,
        1,
        7,
        2,
        0,
        2,
        1,
        3,
    };

    const byte PAD_BYTE_MAPPING[12] = {
        // SW:  1  2  3
        0,
        0,
        0,
        // SW:  8  9 10
        0,
        1,
        1,
        // SW:  15 16 17
        1,
        1,
        2,
        // SW:  22 23 24
        2,
        2,
        2,
    };

    const byte PAD_BIT_MAPPING[12] = {
        // SW:  1  2  3
        9,
        1,
        2,
        // SW:  8  9 10
        7,
        0,
        1,
        // SW:  15 16 17
        6,
        7,
        0,
        // SW:  22 23 24
        5,
        6,
        7,
    };

    const byte UTILITY_BYTE_MAPPING[8] = {
        // SW:  4  5  6  7
        0,
        0,
        0,
        0,
        // SW:  11 12 13 14
        1,
        1,
        1,
        1,
    };

    const byte UTILITY_BIT_MAPPING[8] = {
        // SW:  4  5  6  7
        3,
        4,
        5,
        6,
        // SW:  11 12 13 14
        2,
        3,
        4,
        5,
    };

    const byte ENCODER_BIT_MAPPING[4] = {
        0,
        1,
        2,
        3,
    };
};