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


// 'Led' Class
class Led{
    private:
        int red_pin, green_pin, blue_pin;
        int color[3] = {0, 0, 0}; int target_color[3] = {0, 0, 0}; 
    public:
        // don't use this constructor
        Led(){}; 

        // Do use this constructor
        Led(int red_pin, int green_pin, int blue_pin){
            this->red_pin = red_pin;
            this->green_pin = green_pin;
            this->blue_pin = blue_pin;
            analogWrite(red_pin, 0);
            analogWrite(green_pin, 0);
            analogWrite(blue_pin, 0);
        }

        // Check if Led has reached target color
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

        // set PWM on Led pins to current color values
        void update(){
            analogWrite(red_pin, color[0]);
            analogWrite(green_pin, color[1]);
            analogWrite(blue_pin, color[2]);
        }
};

// Function to change color
void change_colors(Led & l, int red, int green, int blue, int delaytimewithin){
        l.set_target_color(red, green, blue);
        while (!l.is_done()){
            l.tick_target();
            delay(delaytimewithin);
        }
}

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    //pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 0; i < rgbPinsCount; ++i){
        pinMode(rgbPins[i], OUTPUT);
    }
}

// bob will be our 'Led' object
Led bob = Led(rgbPins[0], rgbPins[1], rgbPins[2]);


// Color table
int COLORS[][3] = {
    { 255, 0, 0 }, // red
    { 250, 255, 0 }, // yellow
    { 0, 0, 255 },  // blue
    { 0, 255, 0 }, // green

    { 255, 0, 100 },  // cyan
    { 0, 255, 120 },  // sea green
    { 100, 100, 100 }  // white
};

// number of colors in above table
int NO_COLORS = 7;

// delay times
int delay_between = 700;
int delay_within = 25;

// running loop
void loop() {
    for (int i = 0; i < NO_COLORS; ++i){
        change_colors(bob, COLORS[i][0], COLORS[i][1], COLORS[i][2], delay_within);
        delay(delay_between);
    }
}



