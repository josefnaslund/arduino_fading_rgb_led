/*
 * Arduino RGB LED with fading colors. Christmas decoration?
 * Author: Josef Naslund (my first Arduino project)
 * Date: 2019-11-28
 * For this project you need:
 *    -Arduino UNO compatible board
 *    -At least one RGB LED (common Cathode, like Kjell 90718)
 *    -Three resistors per LED (1x150 ohm for red pin, 2x100 ohm for green/blue)
 *    -Some wires and a breadboard or solder
 *    -Some diffuser for the LED, like household paper or some hot glue
 */


// These are PWM pins you can use: 11, 10, 9, 6, 5, 3
int rgbPins[] = {11, 10, 9};
int rgbPinsCount = 3;

// regular LEDs
int ledPins[] = {13};
int ledPinsCount = 1;

int buttonPin = 2;

// Color table
int COLORS[][3] = {
    { 255, 0, 0 }, // red
    { 250, 255, 0 }, // yellow
    { 0, 0, 255 },  // blue
    { 0, 255, 0 }, // green
    { 255, 0, 100 },  // cyan
    { 0, 255, 120 },  // sea green
    { 255, 255, 255 }  // white
};

// number of colors in above table
int NO_COLORS = 7;

// 'LED' Class
class LED{
private:
    int pin;
    bool on;
    bool waiting;
    unsigned long time_last_update;
    unsigned long time_on_time;
    unsigned long time_interval;


public:
    // Do use this constructor
    LED(int _pin, unsigned long _time_on_time, unsigned long _time_interval){
        on = false;
        waiting = true;
        this->pin = _pin;
        digitalWrite(pin, 0);
        time_on_time= _time_on_time;
        time_interval = _time_interval;
        time_last_update = millis();
    }



    void tick(){
        if (time_on_time > time_interval){
            Serial.println("Error! time_on_time is bigger than time_interval");
        }

        unsigned long time_now = millis();

        if ( waiting && !on && ((time_now - time_last_update) >= time_on_time) ){
            //Serial.print("led on at ");
            //Serial.println(time_now);
            on = true;
            waiting = false;
            digitalWrite(pin, HIGH);
            time_last_update = millis();
        }

        else if (on && ((time_now - time_last_update) >= time_on_time)){
            //Serial.print("led off at ");
            //Serial.println(time_now);
            on = false;
            digitalWrite(pin, LOW);
            //time_last_update = millis();
        }
        
        else if (!on && ((time_now - time_last_update) >= time_interval)){
          waiting = true;
        }

    }
};

// 'RGB_LED' Class
class RGB_LED{
private:
    int current_color;
    int red_pin, green_pin, blue_pin;
    int color[3] = {0, 0, 0}; int target_color[3] = {0, 0, 0}; 
    unsigned long time_last_update;
    unsigned long time_interval_in;
    unsigned long time_interval_between;

    // Check if RGB_LED has reached target color
    bool is_done(){
        bool done = true;
        for (int i = 0; i < 3; ++i){
            if (color[i] != target_color[i])
                done = false;
        }
        return (done);
    }

    // set color to fade to
    void set_target_color(int red, int green, int blue){
        target_color[0] = red; // Red LED pin on 11
        target_color[1] = green; // pin 10
        target_color[2] = blue; // pin 9
    }

    // set 'color' in direction for 'target_color' and call to update()
    void tick_target(){
        if (color[0] < target_color[0])
            color[0]++;
        else if (color[0] > target_color[0]){
            color[0]--;
        }

        if (color[1] < target_color[1])
            color[1]++;
        else if (color[1] > target_color[1]){
            color[1]--;
        }

        if (color[2] < target_color[2])
            color[2]++;
        else if (color[2] > target_color[2]){
            color[2]--;
        }

        // call to update
        update();
    }

    // set PWM on RGB_LED pins to current color values
    void update(){
        analogWrite(red_pin, color[0]);
        analogWrite(green_pin, color[1]);
        analogWrite(blue_pin, color[2]);
    }

public:
    // don't use this constructor
    // RGB_LED(){}; 

    // Do use this constructor
    RGB_LED(int red_pin, int green_pin, int blue_pin, unsigned long _time_interval_in, unsigned long _time_interval_between){
        current_color = 0;
        this->red_pin = red_pin;
        this->green_pin = green_pin;
        this->blue_pin = blue_pin;
        analogWrite(red_pin, 0);
        analogWrite(green_pin, 0);
        analogWrite(blue_pin, 0);
        time_interval_in = _time_interval_in;
        time_interval_between = _time_interval_between;
        time_last_update = millis();
        set_target_color(COLORS[current_color][0], COLORS[current_color][1], COLORS[current_color][2]);
    }



    void tick(){
        unsigned long time_now = millis();
        if ( !is_done() && ((time_now - time_last_update) >= time_interval_in) ){
            tick_target();
            time_last_update = millis();
        }

        else if (is_done() && ((time_now - time_last_update) >= time_interval_between)){
            current_color = (current_color + 1) % NO_COLORS;
            set_target_color(COLORS[current_color][0], COLORS[current_color][1], COLORS[current_color][2]);
            tick_target();
            time_last_update = millis();
        }

    }
};



// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("setup()");
    // initialize digital pin LED_BUILTIN as an output.
    //pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 0; i != rgbPinsCount; ++i){
        pinMode(rgbPins[i], OUTPUT);
    }

    for (int i = 0; i != ledPinsCount; ++i){
        pinMode(ledPins[i], OUTPUT);
    }

    pinMode(buttonPin, INPUT);
}




// delay timings
unsigned long delay_between = 15;
unsigned long delay_within = 300;

// bob will be our 'RGB_LED' object
RGB_LED bob = RGB_LED(rgbPins[0], rgbPins[1], rgbPins[2], delay_between, delay_within);

// alice is on board LED
LED alice = LED(ledPins[0], 500, 1000);


unsigned long start_time = millis();

int button_count = 0;


// running loop
void loop() {
    //Serial.println("Starting loop");
    if (button_count && millis() - start_time >= 10000){
      --button_count;
      start_time = millis();
    }
    
    //if (button_count > 0)
    bob.tick();
    alice.tick();
    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH){
        Serial.print("Button high: ");
        Serial.println(++button_count);
        while (digitalRead(buttonPin) == HIGH){
            ; // do nothing, pause
        }
        start_time = millis();
        Serial.println("Button low");

    }
}
