// Based on the Adafruit_NeoMatrix example for tiled NeoPixel matrices.  Scrolls
// text across four 4x4 NeoPixel grids, arranged as an 8x8 matrix and shows
// simple graphics drawing capabilities.
//
// For more details about using the graphics libraries, refer to:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
//
// Gadget Reboot
//sudo chmod a+rw /dev/ttyUSB0


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define dataPin       6   // Arduino pin 2 is Neopixel data out

// This sketch uses four NeoPixel tiles that each contain 4x4 pixels (16 per tile)
// Four tiles are arranged two wide and two tall for an overall 8x8 matrix
// made from four 4x4 tiles stacked in a square
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
#define PINK  0xF818
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

// arrays holding color config data for scrolling text and for graphics drawings
const uint16_t drawingColors[] = { GREEN, BLUE, CYAN, WHITE, RED, YELLOW, PINK };

String msg     = "Hentai AI";      // text to scroll on display
int    x_size  = matrix.width();   // overall display matrix width
int    y_size  = matrix.height();  // overall display matrix height
int    msglen  = msg.length();     // number of characters in scrolling message
int    x_pos   = matrix.width();   // track where we are in the scrolling message display
int    pass    = 0;                // track how many times message has scrolled

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
    
//    testPixels();       // light up individual pixels at random colors
//    delay(1000);
//    drawLines();        // show how to draw lines between x,y coordinates
//    delay(1000);
//    drawRectangles();   // show how to draw rectangles
///    delay(1000);
///    drawCircles();      // show how to draw circles
///    delay(1000);
    drawTriangles();    // show how to draw triangles
    delay(1000);
    drawBars();         // draw some lines resembling an audio spectrum analyzer
    delay(1000);
  matrix.show();
  delay(100);
}

void testPixels() {
  int rnd;
  matrix.fillScreen(0); // Clears screen
  for (int i = 0; i < x_size; i++) {
    for (int j = 0; j < y_size; j++) {
      rnd = random(0, 7); //slects one of our random 
      matrix.drawPixel(i, j, drawingColors[rnd]);
      matrix.show();
      delay(75);
    }
  }
}

// drawlines works by taking two x,y values then a color
void drawLines() {
  matrix.fillScreen(0);
  matrix.drawLine(0, 0, 23, 12, BLUE);
  matrix.show();
  delay(200);
  matrix.drawLine(23, 0, 0, 12, GREEN);
  matrix.show();
  delay(200);
  matrix.drawLine(12, 0, 12, 12, PINK);
  matrix.show();
  delay(200);
  matrix.drawLine(0, 6, 23, 6, WHITE);
  matrix.show();
  delay(200);
}

void drawRectangles() {
  int rnd;
  matrix.fillScreen(0);
  for (int i = 0; i < matrix.height() / 2 + 1; i++) {
    rnd = random(0, 7);
    matrix.drawRect(i, i, matrix.width() - i * 2 , matrix.height() - i * 2 , drawingColors[rnd]);
    matrix.show();
    delay(200);
  }
}

void drawCircles() {
  int rnd;
  matrix.fillScreen(0);
  for (int i = 0; i < matrix.height(); i++) {
    rnd = random(0, 7);
    matrix.drawCircle(matrix.width() / 2 - 1, matrix.height() / 2 - 1, i + 1, drawingColors[rnd]);
    matrix.show();
    delay(200);
  }
}

void drawTriangles() {
  matrix.fillScreen(0);
  matrix.drawTriangle(0, 0, 22, 0, 12, 12, GREEN);
  matrix.show();
  delay(200);
  matrix.drawTriangle(3, 1, 18, 1, 12, 10, PINK);
  matrix.show();
  delay(200);
  matrix.drawTriangle(6, 2, 15, 2, 12, 8, YELLOW);
  matrix.show();
  delay(200);
  matrix.fillTriangle(8, 3, 14, 3, 12, 7, BLUE);
  matrix.show();
}

void drawBars() {

  int rnd;
  for (int i = 0; i < 10; i++) {
    matrix.fillScreen(0);
    rnd = random(1, 9); 
    matrix.drawLine(0, 12, 0, rnd, WHITE);
    matrix.drawPixel(0, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(1, 12, 1, rnd, WHITE);
    matrix.drawPixel(1, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(2, 12, 2, rnd, WHITE);
    matrix.drawPixel(2, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(3, 12, 3, rnd, WHITE);
    matrix.drawPixel(3, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(4, 12, 4, rnd, WHITE);
    matrix.drawPixel(4, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(5, 12, 5, rnd, WHITE);
    matrix.drawPixel(5, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(6, 12, 6, rnd, WHITE);
    matrix.drawPixel(6, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(7, 12, 7, rnd, WHITE);
    matrix.drawPixel(7, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(8, 12, 8, rnd, WHITE);
    matrix.drawPixel(8, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(9, 12, 9, rnd, WHITE);
    matrix.drawPixel(9, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(10, 12, 10, rnd, WHITE);
    matrix.drawPixel(10, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(11, 12, 11, rnd, WHITE);
    matrix.drawPixel(11, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(12, 12, 12, rnd, WHITE);
    matrix.drawPixel(12, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(13, 12, 13, rnd, WHITE);
    matrix.drawPixel(13, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(14, 12, 14, rnd, WHITE);
    matrix.drawPixel(14, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(15, 12, 15, rnd, WHITE);
    matrix.drawPixel(15, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(16, 12, 16, rnd, WHITE);
    matrix.drawPixel(16, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(17, 12, 17, rnd, WHITE);
    matrix.drawPixel(17, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(18, 12, 18, rnd, WHITE);
    matrix.drawPixel(18, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(19, 12, 19, rnd, WHITE);
    matrix.drawPixel(19, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(20, 12, 20, rnd, WHITE);
    matrix.drawPixel(20, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(21, 12, 21, rnd, WHITE);
    matrix.drawPixel(21, rnd - 1, BLUE);
    matrix.show();

    rnd = random(1, 9); 
    matrix.drawLine(22, 12, 22, rnd, WHITE);
    matrix.drawPixel(22, rnd - 1, BLUE);
    matrix.show();
        
    delay(300);
  }
}
