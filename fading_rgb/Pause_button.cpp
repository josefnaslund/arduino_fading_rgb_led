#include <Arduino.h>
#include "Pause_button.h"


void Pause_button::tick(){
    int buttonState = digitalRead(pin);

    if (!activated && buttonState == HIGH && ((millis() - time_last_activated) > 15) && ((millis() - time_pressed) > 250) ){
        activated = true;
        time_last_activated = millis();
        return;
    }

    if (activated && buttonState == LOW && ((millis() - time_last_activated) > 15)){
        activated = false;
        return;
    }

    if (activated && buttonState == LOW && ((millis() - time_last_activated) <= 15)){
        return;
    }


    if (activated && ( (millis() - time_last_activated) > 10) && (digitalRead(pin) == HIGH)){
        Serial.println("Pause button high: ");
        pressed = true;
        time_last_activated = millis();
        ++button_count;
        while (digitalRead(pin) == HIGH){
            ; // do nothing, pause
        }
        time_pressed = millis();
        Serial.println(button_count);

        // receiver->interact(signal);
        send_interaction();

        // unsigned long start_time = millis();
        Serial.println("Pause button low");
        pressed = false;
        activated = false;
        return;
    }
}

Pause_button::Pause_button(int _pin, I_observer *receiver, const int& signal) : Button(_pin, receiver, signal) {};
