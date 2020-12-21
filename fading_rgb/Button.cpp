#include <Arduino.h>
#include "Button.h"


Button::Button(int _pin, I_interaction *receiver, const int& signal) : I_interact(receiver, signal){
    pin = _pin;
    pressed = false;
    button_count = 0;
    activated = false;
    time_pressed = millis();
    time_last_activated = 0;

}

Button::~Button() {};

void Button::tick() {};
