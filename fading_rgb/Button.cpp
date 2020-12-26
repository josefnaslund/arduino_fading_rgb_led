#include <Arduino.h>
#include "Button.h"


Button::Button(int _pin, const int& signal) : I_subject(signal){
    pin = _pin;
    pressed = false;
    button_count = 0;
    activated = false;
    time_pressed = millis();
    time_last_activated = 0;

}

Button::~Button() {};

void Button::tick() {
    int buttonState = digitalRead(pin);

    // activate button before beeing pressed.
    if (!activated && buttonState == HIGH && ((millis() - time_last_activated) > 15) && ((millis() - time_pressed) > 250) ){
        activated = true;
        time_last_activated = millis();
        return;
    }

    // turning off actually pressed button
    if (pressed && buttonState == LOW){
        pressed = false;
        activated = false;
        Serial.println("Button low");
        return;
    }

    // is this needed?
    if (activated && buttonState == LOW && ((millis() - time_last_activated) > 15)){
        activated = false;
        return;
    }

    // wait for later reading
    if (activated && buttonState == LOW && ((millis() - time_last_activated) <= 15)){
        return;
    }


    // actual turn on button
    if (!pressed && activated && ( (millis() - time_last_activated) > 10) && (digitalRead(pin) == HIGH)){
        Serial.println("Regular button high: ");
        pressed = true;
        time_last_activated = millis();
        ++button_count;
        time_pressed = millis();
        Serial.println(button_count);

        // receiver->interact(signal);
        send_interaction();

        return;
    }
};
