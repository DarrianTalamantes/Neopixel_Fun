//sudo chmod a+rw /dev/ttyACM0 is a peice of code allowing aurdino to have permission to read and write

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

int PIN = 6;
int N_LEDS = 30;

//the 4 variables are number of leds on strip, the info pin, the type of pixal RGB or GRB, and the signal type 400 or 800
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800); //This variable will be used in like every function now

int delay_val = 500;

void setup() {  //This is run only one time when you use the code
  pixels.begin(); //This initializes the Neopixal library 
}

// define color packets!
 uint32_t red = pixels.Color(255,0,0); //This creates a variable for a clor

void loop(){
  // pixal color tutorial each only goes to 255
  //the first number is the neopixal number starting from 0
  pixels.setPixelColor(0, red); //red
  pixels.setPixelColor(1, pixels.Color(0,150,0)); //green
  pixels.setPixelColor(2, pixels.Color(0,0,150)); //blue
  pixels.setPixelColor(3, pixels.Color(150,150,0)); //yellow
  pixels.setPixelColor(4, pixels.Color(0,150,150)); //cyan
  pixels.setPixelColor(5, pixels.Color(150,0,150)); //magenta
  pixels.setPixelColor(6, pixels.Color(150,150,150)); //white
  pixels.setPixelColor(7, pixels.Color(150,50,0)); //orange
  pixels.setPixelColor(8, pixels.Color(0,0,0)); //turns off neopixal

  pixels.setBrightness(64); //Changed the brightness of the strip. Range is 0-255
  
  pixels.show(); //This sends the updated pixel color to the harware!!!!
  delay(delay_val); //Delay for a period of time in miliseconds. We put this at the end of the loop so it doesnt update ridiculously fast
  }
