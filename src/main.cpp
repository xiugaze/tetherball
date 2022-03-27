#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 6
#define LED_COUNT 525
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button


bool direction = true;  // true == counterclockwise (away from origin)

int prevPosition = 0;
int currentPosition = 1;
int nextPosition = 2; 

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

  if(currentPosition == 516 && direction) {
    nextPosition = 11;
    currentPosition = 1;
    prevPosition = 515;

  } else if (currentPosition == 20 && !direction) {
    prevPosition = 525;
    currentPosition = 525;
    nextPosition = 524;
  } else {
    currentPosition = direction ? currentPosition + 5 : currentPosition - 5;
    nextPosition = direction ? nextPosition + 5 : nextPosition - 5;
    prevPosition = direction ? prevPosition + 5 : prevPosition - 5;
  }


  uint32_t red = strip.Color(255, 0, 0);
  uint32_t orange = strip.Color(255, 100, 0);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t black = strip.Color(0, 0, 0);


  strip.fill(black, prevPosition, 10);
  strip.fill(orange, currentPosition, 10);
  strip.fill(black, nextPosition, 10);
  delay(4000);

  /*
  strip.setPixelColor(prevPosition, 0,0,0);
  strip.setPixelColor(currentPosition, 255,255,255);
  strip.setPixelColor(nextPosition, 0,0,0);
  //strip.print(String(currentPosition));
  //delayMicroseconds(1);
  */

  strip.show();
}