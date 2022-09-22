
//sudo chmod a+rw /dev/ttyACM0 is a peice of code allowing aurdino to have permission to read and write
// sudo chmod a+rw /dev/ttyUSB0 this might be it too

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

// DATA PIN
// If you want to use a different data pin on your microcontroller CHANGE THIS!
#define DATA_PIN 6

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

// Matrix setup params
// 13 by 23 grid
// pixal zero starts at top right, flows down in columns, all columns flow in same direction
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(23, 13, DATA_PIN,
NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]); // The way the display is coded makes this necessary. Without it the first word is white
}

int x    = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 3); // This sets the place where light will start. 0,0 is top left
  matrix.print(F("Howdy"));
  // This essentially cycles through the colors in the colors list
  if(--x < -36) { // This decrements x and then checks if the entire word is off the grid (each letter is 6 pixals so -36 will ensure it is all off the grid)
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}
