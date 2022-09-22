//sudo chmod a+rw /dev/ttyUSB0


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// DATA PIN
// If you want to use a different data pin on your microcontroller CHANGE THIS!
#define DATA_PIN 6
#define NUMPIXELS 299
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

// Matrix setup params
// 13 by 23 grid
// pixal zero starts at top right, flows down in columns, all columns flow in same direction
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(1, 299, DATA_PIN,
NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);

void setup() {
    matrix.begin();
}



void loop(){
  colorWipe(matrix.Color(0, 255, 0), 20); // Green
  colorWipe(matrix.Color(255, 0, 0), 20); // Red
  }




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i< NUMPIXELS; i++) {
      matrix.drawPixel(0, i, c);
      matrix.show();
      delay(wait);
  }
}
