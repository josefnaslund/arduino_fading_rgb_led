#include <Arduino.h>
#include "Pause_button.h"


void Pause_button::tick(){
    int buttonState = digitalRead(pin);
    if (buttonState == HIGH){
        Serial.print("Button high: ");
        pressed = true;
        Serial.println(++button_count);
        while (digitalRead(pin) == HIGH){
            ; // do nothing, pause
        }
        // unsigned long start_time = millis();
        Serial.println("Button low");
        pressed = false;

    }
}

Pause_button::Pause_button(int _pin) : Button(_pin) {};
