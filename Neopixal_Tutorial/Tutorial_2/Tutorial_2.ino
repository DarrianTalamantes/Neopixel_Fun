// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
//  chase(strip.Color(255, 0, 0)); // Red
//  chase(strip.Color(0, 255, 0)); // Green
//  chase(strip.Color(0, 0, 255)); // Blue

  ranlite(strip.Color(0, 150, 100)); // Cyan
  strip.clear();
}

// This method makes a chain of 4 pixals move all the way down your strand
static void chase(uint32_t c) { //unit32_t is avariable type used for neopixals
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // sets pixel a few steps back to off.
      strip.show();
      delay(250);
  }
}


// This method will try to randomly light up pixals up to the number on your strand. Will light up same though so not all will light up.
static void ranlite(uint32_t r) {
  randomSeed(analogRead(0));
  for(uint16_t i = 0; i<strip.numPixels(); i++){
    int ran1 = random(0,9);
    strip.setPixelColor(ran1  , r);
    strip.show();
    delay(200);
    }
  }
