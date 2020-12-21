#ifndef I_INTERACT_H
#define I_INTERACT_H

#include "I_interaction.h"

/**
 * Interface for objects (e.g. buttons) sending signals to other objects (e.g. LEDs/RGB_LEDs).
 */
class I_interaction;

class I_interact {
protected:
    I_interaction *receiver;
    int signal;

public:
    I_interact(I_interaction *receiver, const int& signal) : receiver(receiver), signal(signal) {};
    virtual ~I_interact() {};
    
    void send_interaction() {receiver->interact(signal);};
};

#endif
