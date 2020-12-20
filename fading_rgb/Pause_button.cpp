#include <Arduino.h>
#include "Pause_button.h"


void Pause_button::tick(){
    int buttonState = digitalRead(pin);
    if (!activated && buttonState == HIGH){
      activated = true;
      time_first_pressed = millis();
      return;
    }
    if (activated && ( (millis() - time_first_pressed) > 4) && (digitalRead(pin) == LOW)){
      activated = false;
      return;
    }    
    
    if (activated && ( (millis() - time_first_pressed) > 4) && (digitalRead(pin) == HIGH)){
        Serial.println("Pause button high: ");
        pressed = true;
        ++button_count;
        while (digitalRead(pin) == HIGH){
            ; // do nothing, pause
        }
        Serial.println(button_count);

        // unsigned long start_time = millis();
        Serial.println("Pause button low");
        pressed = false;
        activated = false;
        return;
    }
}

Pause_button::Pause_button(int _pin) : Button(_pin) {};
