#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H

#include "Button.h"

class Pause_button : public Button {
    public:
        Pause_button(int _pin);
        void tick() override;
};

#endif
