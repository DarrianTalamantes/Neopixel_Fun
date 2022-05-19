//sudo chmod a+rw /dev/ttyUSB0

#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 20
#define bright 80


Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  
}




void loop() {
  // put your main code here, to run repeatedly:
  //This will turn all pixals on
  //colorWipe(strip.Color(0,   255,   20), 100);

//This loop will use the ranlite method to turn lights cyan and then on the fifth round pink.
  
  for(uint16_t i = 0; i < 4; i++){
    ranlite(strip.Color(0, 250, 200)); // Cyan
    strip.clear();
    if(i == 3){
      ranlite(strip.Color(250, 0, 200)); // Pink
      strip.clear();
    }
  }
  
}


// This method will try to randomly light up pixals up to the number on your strand. Will light up same though so not all will light up.
static void ranlite(uint32_t r) {
  randomSeed(analogRead(0));
  for(uint16_t i = 0; i<strip.numPixels(); i++){
    int ran1 = random(0,(N_LEDS-1));
    strip.setPixelColor(ran1  , r);
    strip.show();
    delay(200);
    }
  }

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

  
