#ifndef BUTTON_H
#define BUTTON_H

#include "I_interact.h"

class Button : public I_interact{
protected:
    int pin;
    bool pressed;
    int button_count;
    bool activated;
    unsigned long time_last_activated;
    unsigned long time_pressed;



public:
    Button(int _pin, I_interaction *receiver, const int& signal);
    virtual ~Button();

    // implement!
    virtual void tick();

    bool is_pressed() {return pressed;}

};

#endif
