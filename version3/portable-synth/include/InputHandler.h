#pragma once

class KeyboardHandler
{
public:
    virtual void keyboardEvent(int button, bool pressed);
};

class EncoderHandler
{
public:
    virtual void encoderEvent(int encoder, bool moved_left);
};

class MenuButtonHandler
{
public:
    enum BUTTONS
    {
        MAIN,
        LEFT,
        RIGHT,
    };

    virtual void menuButtonEvent(BUTTONS button, bool pressed);
};