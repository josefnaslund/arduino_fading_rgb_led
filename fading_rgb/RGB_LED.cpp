#include <Arduino.h>
#include "RGB_LED.h"

// defined in .ino file
extern int COLORS[][3];
extern int NO_COLORS;

bool RGB_LED::is_done(){
    bool done = true;
    for (int i = 0; i < 3; ++i){
        if (color[i] != target_color[i])
            done = false;
    }
    return (done);
}

// set color to fade to
void RGB_LED::set_target_color(int red, int green, int blue){
    target_color[0] = red; // Red LED pin on 11
    target_color[1] = green; // pin 10
    target_color[2] = blue; // pin 9
}

// set 'color' in direction for 'target_color' and call to update()
void RGB_LED::tick_target(){
    if (color[0] < target_color[0])
        color[0]++;
    else if (color[0] > target_color[0]){
        color[0]--;
    }

    if (color[1] < target_color[1])
        color[1]++;
    else if (color[1] > target_color[1]){
        color[1]--;
    }

    if (color[2] < target_color[2])
        color[2]++;
    else if (color[2] > target_color[2]){
        color[2]--;
    }

    // call to update
    update();
}

// set PWM on RGB_LED pins to current color values
void RGB_LED::update(){
    analogWrite(red_pin, color[0]);
    analogWrite(green_pin, color[1]);
    analogWrite(blue_pin, color[2]);
}

// Do use this constructor
RGB_LED::RGB_LED(int red_pin, int green_pin, int blue_pin, unsigned long _time_interval_in, unsigned long _time_interval_between){
    current_color = 0;
    this->red_pin = red_pin;
    this->green_pin = green_pin;
    this->blue_pin = blue_pin;
    analogWrite(red_pin, 0);
    analogWrite(green_pin, 0);
    analogWrite(blue_pin, 0);
    time_interval_in = _time_interval_in;
    time_interval_between = _time_interval_between;
    time_last_update = millis();
    set_target_color(COLORS[current_color][0], COLORS[current_color][1], COLORS[current_color][2]);
}


void RGB_LED::tick(){
    unsigned long time_now = millis();
    if ( !is_done() && ((time_now - time_last_update) >= time_interval_in) ){
        tick_target();
        time_last_update = millis();
    }

    else if (is_done() && ((time_now - time_last_update) >= time_interval_between)){
        current_color = (current_color + 1) % NO_COLORS;
        set_target_color(COLORS[current_color][0], COLORS[current_color][1], COLORS[current_color][2]);
        tick_target();
        time_last_update = millis();
    }
}

void RGB_LED::interact(const int& signal){
    Serial.print("RGB_LED got an interact(");
    Serial.print(signal);
    Serial.println(") signal");
    if (signal == 0){
        // send to black color, and retry last color
        target_color[0] = 0;
        target_color[1] = 0;
        target_color[2] = 0;
        if (--current_color < 0)
            current_color = NO_COLORS - 1;
    }

}
