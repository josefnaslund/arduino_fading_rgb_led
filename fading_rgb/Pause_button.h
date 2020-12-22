#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H

#include "Button.h"

class Pause_button : public Button {
public:
    Pause_button(int _pin, I_observer *receiver, const int& signal);
    ~Pause_button() = default;
    void tick() override;
};

#endif
