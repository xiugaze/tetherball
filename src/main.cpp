#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 6
#define LED_COUNT 526
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button


bool direction = true;  // true == counterclockwise (away from origin)

int prevPosition = 1;
int currentPosition = 2;
int nextPosition =3; 

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
    nextPosition = 3;
    currentPosition = 2;
    prevPosition = 1;
  } else if (currentPosition == 1 && !direction) {
    prevPosition = 526;
    currentPosition = 525;
    nextPosition = 524;
  } else {
    currentPosition = direction ? currentPosition + 1 : currentPosition - 1;
    nextPosition = direction ? nextPosition + 1 : nextPosition - 1;
    prevPosition = direction ? prevPosition + 1 : prevPosition - 1;
  }


  uint32_t red = strip.Color(255, 0, 0);
  uint32_t orange = strip.Color(255, 100, 0);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t black = strip.Color(0, 0, 0);


  strip.fill(black, prevPosition - 5, 10);
  strip.fill(orange, currentPosition - 5, 10);
  strip.fill(black, nextPosition - 5, 10);
  delay(100);

  /*
  strip.setPixelColor(prevPosition, 0,0,0);
  strip.setPixelColor(currentPosition, 255,255,255);
  strip.setPixelColor(nextPosition, 0,0,0);
  //strip.print(String(currentPosition));
  //delayMicroseconds(1);
  */

  strip.show();
}