#pragma once

#include <Arduino.h>

class Input {
public:
    void begin();

    void update();

    enum MENU_BUTTONS {
        MENU_MAIN,
        MENU_LEFT,
        MENU_RIGHT,
    };

    enum KEYBOARD_BUTTONS {
        KEYBOARD_FIRST = 0,
        KEYBOARD_C1 = KEYBOARD_FIRST,
        KEYBOARD_CS1,
        KEYBOARD_D1,
        KEYBOARD_DS1,
        KEYBOARD_E1,
        KEYBOARD_F1,
        KEYBOARD_FS1,
        KEYBOARD_G1,
        KEYBOARD_GS1,
        KEYBOARD_A1,
        KEYBOARD_AS1,
        KEYBOARD_B1,
        KEYBOARD_C2,
        KEYBOARD_CS2,
        KEYBOARD_D2,
        KEYBOARD_DS2,
        KEYBOARD_E2,
        KEYBOARD_F2,
        KEYBOARD_FS2,
        KEYBOARD_G2,
        KEYBOARD_GS2,
        KEYBOARD_A2,
        KEYBOARD_AS2,
        KEYBOARD_B2,
        KEYBOARD_LAST = KEYBOARD_B2,
    };



private:
    void readData();

    void updateKeyboard(KEYBOARD_BUTTONS button, bool pressed);
    void updatePad(int pad, bool pressed);
    void updateMenu(MENU_BUTTONS button, bool pressed);

    byte buttonStates[8] = {0,0,0,0,0,0,0,0}; 
    byte lastButtonStates[8] = {0,0,0,0,0,0,0,0};

    const byte MENU_BIT_MAPPIN[3] = {5, 4, 6};

    const byte KEYBOARD_BYTE_MAPPING[24] = {
// SW:  25 18 26 19 27 28 20 36 21 37 29 38
        3, 2, 3, 2, 3, 3, 2, 4, 2, 4, 3, 4,
// SW:  39 30 40 31 41 42 32 35 33 43 34 44
        4, 3, 4, 3, 5, 5, 3, 4, 4, 5, 3, 5,
    };

    const byte KEYBOARD_BIT_MAPPING[24] = {
// SW:  25 18 26 19 27 28 20 36 21 37 29 38
        0, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5,
// SW:  39 30 40 31 41 42 32 35 33 43 34 44
        6, 5, 7, 6, 0, 1, 7, 2, 0, 2, 1, 3,
    };

    const byte PAD_BYTE_MAPPING[12] = {
// SW:  1  2  3
        0, 0, 0,
// SW:  8  9 10
        0, 1, 1,
// SW:  15 16 17
        1, 1, 2,
// SW:  22 23 24
        2, 2, 2,
    };

    const byte PAD_BIT_MAPPING[12] = {
// SW:  1  2  3
        9, 1, 2,
// SW:  8  9 10
        7, 0, 1,
// SW:  15 16 17
        6, 7, 0,
// SW:  22 23 24
        5, 6, 7,
    };
}; 