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
  
  //Uses the chase function 
//  chase(strip.Color(255, 0, 0)); // Red
//  chase(strip.Color(0, 255, 0)); // Green
//  chase(strip.Color(0, 0, 255)); // Blue

//This loop will use the ranlite method to turn lights cyan and then on the fifth round pink.
/*
  for(uint16_t i = 0; i < 4; i++){
    ranlite(strip.Color(0, 150, 100)); // Cyan
    strip.clear();
    if(i == 3){
      ranlite(strip.Color(150, 0, 100)); // Pink
      strip.clear();
    }
  }
  */
  
  //This cahnges neopixals by using a range
  int half =  (strip.numPixels()/2) + (strip.numPixels()%2);
  strip.fill(strip.Color(255, 0, 0), 0, half);
  strip.fill(strip.Color(0, 0, 255), half,strip.numPixels());
  strip.show();


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










  
