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

#include "LED.h"
#include "RGB_LED.h"
#include "Pause_button.h"

// These are PWM pins you can use: 11, 10, 9, 6, 5, 3
int rgbPins[] = {11, 10, 9};
int rgbPinsCount = 3;

// regular LEDsf
int ledPins[] = {13, 12};
int ledPinsCount = 2;

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

int button_count = 0;

LED alice = LED(ledPins[0], 50, 100);
LED alice2 = LED(ledPins[1], 1000, 2000);


// button
Pause_button btn_Pause = Pause_button(buttonPin);

unsigned long start_time = millis();

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
    alice2.tick();
    btn_Pause.tick();
}
