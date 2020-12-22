#ifndef I_OBSERVER_H
#define I_OBSERVER_H


/**
 * Interface for objects (e.g. RGB_LEDs/LEDs) receiving signals from I_interact objects (e.g. Buttons)
 */
class I_observer {

public:
    I_observer() = default;
    virtual ~I_observer() = default;
    virtual void interact(const int& _signal) = 0;
    virtual void tick() = 0;
};

#endif
