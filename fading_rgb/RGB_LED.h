#ifndef RGB_LED_H
#define RGB_LED_H

#include "I_interaction.h"

// 'RGB_LED' Class
class RGB_LED : public I_interaction {
private:
    int current_color;
    int red_pin, green_pin, blue_pin;
    int color[3] = {0, 0, 0}; 
    int target_color[3] = {0, 0, 0}; 
    unsigned long time_last_update;
    unsigned long time_interval_in;
    unsigned long time_interval_between;

    // Check if RGB_LED has reached target color
    bool is_done();

    // set color to fade to
    void set_target_color(int red, int green, int blue);

    // set 'color' in direction for 'target_color' and call to update()
    void tick_target();

    // set PWM on RGB_LED pins to current color values
    void update();

public:
    // Do use this constructor
    RGB_LED(int red_pin, int green_pin, int blue_pin, unsigned long _time_interval_in, unsigned long _time_interval_between);

    void tick();

    void interact(const int& signal) override;
};

#endif
