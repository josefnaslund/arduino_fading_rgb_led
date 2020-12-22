/*
 * Learning microcontroller interaction. This project does... nothing useful
 * really... An RGB LED shifting through colors while regular LEDs are blinking
 * at different tempos. All while listening to a push button.
 * Project uses C++ classes with interfaces for interacion between buttons and LEDs.
 * Author: Josef Naslund
 * Date: 2020-12
 * For this project you need:
 *    -Arduino UNO compatible board, or similar. 6 GPIO pins, three being PWM
 *      capable.
 *    -At least one RGB LED (common Cathode, like Kjell 90718 - discontinued)
 *    -Three resistors per LED (1x150 ohm for red pin, 2x100 ohm for green/blue)
 *    -Resisors for regular LEDs.
 *    -Pulldown resistor for switch.
 *    -Switch.
 *    -Some wires and a breadboard or solder
 *    -Some diffuser for the RGB LED, like thin paper or some hot glue
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
I_observer *bob = new RGB_LED(rgbPins[0], rgbPins[1], rgbPins[2], delay_between, delay_within);

// regular LEDs (so far...)
LED alice = LED(ledPins[0], 50, 200);
LED alice2 = LED(ledPins[1], 1000, 2000);

// button
Pause_button btn_Pause = Pause_button(buttonPin, bob, 0);

unsigned long start_time = millis();

// running loop
void loop() {

    (*bob).tick();
    alice.tick();
    alice2.tick();
    btn_Pause.tick();

}
