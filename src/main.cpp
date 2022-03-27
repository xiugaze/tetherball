#include <Arduino.h>
#include <Adafruit_NeoPXL8.h>

#define NUM_LED 526  

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button

int8_t pins[8] = { 13, 12, 11, 10, SCK, 5, 9, 6 };
Adafruit_NeoPXL8 leds(NUM_LED, pins, NEO_GRB);

bool direction = true;  // true == counterclockwise (away from origin)

int prevPosition = 526;
int currentPosition = 1;
int nextPosition =2; 

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
    nextPosition = 2;
    currentPosition = 1;
    prevPosition = 526;
  } else if (currentPosition == 1 && !direction) {
    prevPosition = 1;
    currentPosition = 526;
    nextPosition = 525;
  } else {
    currentPosition = direction ? currentPosition + 1 : currentPosition - 1;
    nextPosition = direction ? nextPosition + 1 : nextPosition - 1;
    prevPosition = direction ? prevPosition + 1 : prevPosition - 1;
  }


  leds.setPixelColor(prevPosition, 0x000000);
  leds.setPixelColor(currentPosition, 0xFFFFFF);
  leds.setPixelColor(nextPosition, 0x000000);
  delay(10);
}