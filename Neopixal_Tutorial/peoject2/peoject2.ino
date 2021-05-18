//sudo chmod a+rw /dev/ttyACM0 is a peice of code allowing aurdino to have permission to read and write

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

#define PIN 6
#define N_LEDS 60
int delay_val = 40;
int sensorPin=7;
boolean val =0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin(); //This initializes the Neopixal library
  pixels.show();
}

// define color packets!
uint32_t cyan = pixels.Color(  0, 175,   100);
uint32_t magenta =  pixels.Color(150, 0, 150);
uint32_t spring_green =  pixels.Color(12 , 245, 0);
uint32_t white =  pixels.Color(150 , 150, 150);




void loop() {
  // put your main code here, to run repeatedly:
  val =digitalRead(sensorPin);
  Serial.println (val);
  if (val==HIGH) {
    chase(magenta, cyan);
  }
  else {
    pixels.fill(cyan);

  }
  // chase(magenta, cyan);
  /*
  Revchase(spring_green, cyan);
  chase(white, cyan);
  */

  pixels.show(); //This sends the updated pixel color to the harware!!!!
  delay(delay_val); //Delay for a period of time in miliseconds.
}

// Sends four pixels down in a different color
static void chase(uint32_t c, uint32_t c2 ) { //unit32_t is avariable type used for neopixals
  for(uint16_t i=0; i<pixels.numPixels()+4; i++) {
      pixels.setPixelColor(i  , c); // Draw new pixel
      pixels.setPixelColor(i-4, c2); // sets pixel a few steps back to off.
      pixels.show();
      delay(10);
  }
}

// Sends 4 pixals in the oppisite direction  
static void Revchase(uint32_t c, uint32_t c2 ) { //unit32_t is avariable type used for neopixals
  for(uint16_t i=pixels.numPixels(); i>4-4; i--) {
      pixels.setPixelColor(i  , c); // Draw new pixel
      pixels.setPixelColor(i+4, c2); // sets pixel a few steps back to off.
      pixels.show();
      delay(20);
  }
}
