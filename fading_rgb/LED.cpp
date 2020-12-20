#include <Arduino.h>
#include "LED.h"

LED::LED(int _pin, unsigned long _time_on_time, unsigned long _time_interval){
    on = false;
    waiting = true;
    this->pin = _pin;
    digitalWrite(pin, 0);
    time_on_time= _time_on_time;
    time_interval = _time_interval;
    time_last_update = millis();
}



void LED::tick(){
    if (time_on_time > time_interval){
        Serial.println("Error! time_on_time is bigger than time_interval");
    }

    unsigned long time_now = millis();

    if ( waiting && !on && ((time_now - time_last_update) >= time_on_time) ){
        //Serial.print("led on at ");
        //Serial.println(time_now);
        on = true;
        waiting = false;
        digitalWrite(pin, HIGH);
        time_last_update = millis();
    }

    else if (on && ((time_now - time_last_update) >= time_on_time)){
        //Serial.print("led off at ");
        //Serial.println(time_now);
        on = false;
        digitalWrite(pin, LOW);
        //time_last_update = millis();
    }

    else if (!on && ((time_now - time_last_update) >= time_interval)){
        waiting = true;
    }

}
