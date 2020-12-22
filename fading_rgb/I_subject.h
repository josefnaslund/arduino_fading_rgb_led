#ifndef I_SUBJECT_H
#define I_SUBJECT_H

#include "I_observer.h"

/**
 * Interface for objects (e.g. buttons) sending signals to other objects (e.g. LEDs/RGB_LEDs).
 */
class I_observer;

class I_subject {
protected:
    I_observer **receiver_ptr;
    int receiver_count;
    int signal;

public:
    I_subject(const int& signal);
    void add_observer(I_observer *receiver);
    virtual ~I_subject();

    virtual void tick() = 0;

    void send_interaction(); 
};

#endif
