#include <Arduino.h>
#include "Button.h"


Button::Button(int _pin){
    pin = _pin;
    pressed = false;
    button_count = 0;
}
