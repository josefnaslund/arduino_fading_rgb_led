#include <Arduino.h>
#include "Button.h"


Button::Button(int _pin, I_observer *receiver, const int& signal) : I_subject(receiver, signal){
    pin = _pin;
    pressed = false;
    button_count = 0;
    activated = false;
    time_pressed = millis();
    time_last_activated = 0;

}

Button::~Button() {};

void Button::tick() {};
