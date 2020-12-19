#ifndef LED_H
#define LED_H

// 'LED' Class
class LED{
private:
    int pin;
    bool on;
    bool waiting;
    unsigned long time_last_update;
    unsigned long time_on_time;
    unsigned long time_interval;


public:
    // Do use this constructor
    LED(int _pin, unsigned long _time_on_time, unsigned long _time_interval);

    void tick();
};

#endif
