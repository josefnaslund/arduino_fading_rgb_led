#ifndef I_SUBJECT_H
#define I_SUBJECT_H

#include "I_observer.h"

/**
 * Interface for objects (e.g. buttons) sending signals to other objects (e.g. LEDs/RGB_LEDs).
 */
class I_observer;

class I_subject {
protected:
    I_observer *receiver;
    int signal;

public:
    I_subject(I_observer *receiver, const int& signal) : receiver(receiver), signal(signal) {};
    virtual ~I_subject() {};

    void send_interaction() {receiver->interact(signal);};
};

#endif
