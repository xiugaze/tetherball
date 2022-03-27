#include <Arduino.h>
#include <Adafruit_NeoPXL8.h>


#define NUM_LED 526  

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button

int8_t pins[8] = { 13, 12, 11, 10, SCK, 5, 9, 6 };
Adafruit_NeoPXL8 leds(NUM_LED, pins, NEO_GRB);

bool direction = true; 
int currentPosition = 1;

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

  if(BUTTON_BLUE_PIN == LOW) {
    direction = !direction;
  }

  if(currentPosition == 526 && direction) {
    currentPosition = 1;
  } else if (currentPosition == 1 && !direction) {
    currentPosition = 526;
  } else {
    currentPosition = direction ? currentPosition + 1 : currentPosition - 1;
  }
  leds.setPixelColor(currentPosition - 1, 0x000000);
  leds.setPixelColor(currentPosition, 0xFFFFFF);
  leds.setPixelColor(currentPosition + 1, 0x000000);
  delay(10);
}