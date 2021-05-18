/* 
  Example "Protest scroller" for 8x8 WS2812 "NeoPixel Display
  Assumes you are running a standard Arduino ATMega328 compatible board
*/
//sudo chmod a+rw /dev/ttyACM0 is a peice of code allowing aurdino to have permission to read and write


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// DATA PIN
// If you want to use a different data pin on your microcontroller CHANGE THIS!
#define DATA_PIN 6

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

// Matrix setup params
// 8 by 8 grid
// pixal zero starts at top right, flows down in columns, all columns flow in same direction
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, DATA_PIN,
NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);


// Edit this
// The important stuff, your message and colors

char* Text[]= {"WELCOME", "TO","THE","CLUSTER"};
const uint16_t colors[] = {
  matrix.Color(255, 0, 255), matrix.Color(100, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};
int brightness = 80;
// End Edit

int numMode = arr_len(Text)-1;
int numColor = arr_len(colors)-1;
int pixelPerChar = 4;
int maxDisplacement;
int mode = 0;

void setup() { 
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  matrix.setTextColor(colors[0]);
}

int y = matrix.height();
int x = matrix.width();
int pass = 0;
int line_pass = 0;

void loop() {
    
  // if mode greater than numMode reset
  if (mode > numMode) { mode = 0; }
  
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  scroll(Text[mode],15);
}

// this does the magic of scrolling
void scroll(char* message,int delays) {
  maxDisplacement = strlen(message) * pixelPerChar + matrix.width();
  if(++line_pass > matrix.width()) line_pass = 0;
  matrix.print(String(message));
  if(--x < -maxDisplacement) {
    x = matrix.width();
    if(++pass >= numColor) { pass = 0;  };
    matrix.setTextColor(colors[pass]);
    mode++;
  }
  matrix.show();
  delay(delays);
}
