#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 6
#define LED_COUNT 526
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button


bool direction = true;  // true == counterclockwise (away from origin)

int prevPosition = 526;
int currentPosition = 1;
int nextPosition =2; 

int currentStateRed;
int currentStateBlue;


void setup() {
  Serial.begin(9600);
  
  strip.begin();
  //strip.setBrightness(100);
  strip.show();

  pinMode(BUTTON_BLUE_PIN, INPUT_PULLUP); // active low button
  pinMode(BUTTON_RED_PIN, INPUT_PULLUP); // active low button
}

void loop() {
  currentStateBlue = digitalRead(BUTTON_BLUE_PIN);
  currentStateRed = digitalRead(BUTTON_RED_PIN);

  if(BUTTON_BLUE_PIN == HIGH) {
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


  strip.setPixelColor(prevPosition, 0,0,0);
  strip.setPixelColor(currentPosition, 255,255,255);
  strip.setPixelColor(nextPosition, 0,0,0);
  //strip.print(String(currentPosition));
  delay(500);
  strip.show();
}