#ifndef I_INTERACTION_H
#define I_INTERACTION_H


/**
 * Interface for objects (e.g. RGB_LEDs/LEDs) receiving signals from I_interact objects (e.g. Buttons)
 */
class I_interaction {

public:
    I_interaction() = default;
    virtual ~I_interaction() = default;
    virtual void interact(const int& _signal) = 0;
    virtual void tick() = 0;
};

#endif
