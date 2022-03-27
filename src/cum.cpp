#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 6
#define LED_COUNT 525
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int BUTTON_BLUE_PIN = 2; // pin for blue button
const int BUTTON_RED_PIN = 3; // pin for red button


bool direction = true;  // true == counterclockwise (away from origin)
 

int currentStateRed;
int currentStateBlue;

int currentLed = 10;


void setup() {
  Serial.begin(9600);
  
  strip.begin();
  //strip.setBrightness(100);
  strip.show();

  pinMode(BUTTON_BLUE_PIN, INPUT_PULLUP); // active low button
  pinMode(BUTTON_RED_PIN, INPUT_PULLUP); // active low button
}

void loop() {

  uint32_t red = strip.Color(255, 0, 0);
  uint32_t orange = strip.Color(255, 100, 0);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t black = strip.Color(0, 0, 0);


  strip.fill(black, currentLed - 10, 5);
  strip.fill(green, currentLed - 5, 10);
  strip.fill(black, currentLed, 5);

  if(currentLed == 525) {
    strip.fill(black, LED_COUNT - 5, 5);
    currentLed = 10;
  }
  
  currentLed += 1;
  //delay(50);



  strip.show();
}