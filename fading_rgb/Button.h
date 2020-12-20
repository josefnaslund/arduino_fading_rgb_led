#ifndef BUTTON_H
#define BUTTON_H

class Button {
    protected:
        int pin;
        bool pressed;
        int button_count;
        bool activated;
        unsigned long time_first_pressed;



    public:
        Button(int _pin);
        virtual ~Button();

        // implement!
        virtual void tick();

        bool is_pressed() {return pressed;}

};

#endif
