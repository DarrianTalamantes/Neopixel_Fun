// Code by Darrian Talamantes (darrianrtalamantes6@gmail.com)
// Based off of code Adafruit_NeoMatrix example for tiled NeoPixel matrices
//
// For more details about using the graphics libraries, refer to:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
//
//sudo chmod a+rw /dev/ttyUSB0


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy  (I actually have no idea what this does)
#endif

#define dataPin       6   // Arduino pin 6 is Neopixel data out

// This sketch uses neopixal strands that are layed out in a 23 x 13 matrix
#define matrixWidth   23   // Individual matrix tiles are 4 pixels wide
#define matrixHeight  13   // Individual matrix tiles are 4 pixels high
#define tilesX        1   // Using two 4x4 tiles wide
#define tilesY        1   // Using two 4x4 tiles high


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(matrixWidth, matrixHeight, tilesX, tilesY, dataPin,
                            NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

// Color definitions uses RGB565
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define PINK     0xF818
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

// arrays holding color config data for scrolling text and for graphics drawings
const uint16_t drawingColors[] = { GREEN, BLUE, CYAN, WHITE, RED, YELLOW, PINK };

// Variables
int    x_size  = matrix.width();   // overall display matrix width
int    y_size  = matrix.height();  // overall display matrix height
int    x_pos   = matrix.width();   // track where we are in the scrolling message display

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(drawingColors[0]);
  Serial.println("NeoMatrix pixel grid test");
  Serial.println((String)"Matrix Pixel Width x Height: " + x_size + " x " + y_size);
}

void loop() {
  matrix.fillScreen(0);       // clear display
  matrix.setCursor(x_pos, 0); // set cursor at current horizontal scrolling position and top of display (y=0)

    
  drawFace();
  delay(40);
  drawFace2();
  delay(40);

}



void drawFace() {
  int rnd;
  matrix.fillScreen(0);
  for (int i = 0; i < matrix.height() / 2 + 1; i++) {
    rnd = random(0, 7);
    matrix.fillRect(2, 1, 4, 5, WHITE);
    matrix.fillRect(17, 1, 4, 5, WHITE);
    matrix.fillCircle(11, 8, 2, BLUE);
    matrix.show();
    delay(200);
  }
}

void drawFace2() {
  int rnd;
  matrix.fillScreen(0);
  for (int i = 0; i < matrix.height() / 2 + 1; i++) {
    rnd = random(0, 7);
    matrix.fillRect(2, 2, 6, 3, WHITE);
    matrix.fillRect(17, 2, 6, 3, WHITE);
    matrix.fillTriangle(12, 6, 9, 9, 15, 9, PINK);
    matrix.show();
    delay(200);
  }
}
