#include <Arduino.h>
#include <Adafruit_NeoPXL8.h>


#define NUM_LED 526  

const int BUTTON_BLUE_PIN = 7; // pin for blue button
const int BUTTON_RED_PIN = 8; // pin for red button

int8_t pins[8] = { 13, 12, 11, 10, SCK, 5, 9, 6 };
Adafruit_NeoPXL8 leds(NUM_LED, pins, NEO_GRB);

int currentStateRed;
int currentStateBlue;


void setup() {
  Serial.begin(9600);
  
  leds.begin();
  leds.setBrightness(100);

  pinMode(BUTTON_BLUE_PIN, INPUT_PULLUP); // active low button
  pinMode(BUTTON_RED_PIN, INPUT_PULLUP); // active low button
}


void loop() {
  currentStateBlue = digitalRead(BUTTON_BLUE_PIN);
  currentStateRed = digitalRead(BUTTON_RED_PIN);

  leds.setPixelColor()


}