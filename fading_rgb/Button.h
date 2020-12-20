#ifndef BUTTON_H
#define BUTTON_H

class Button {
    protected:
        int pin;
        bool pressed;
        int button_count;



    public:
        Button(int _pin);

        // implement!
        virtual void tick();

        bool is_pressed() {return pressed;}

};

#endif
