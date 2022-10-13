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
#define BUTTON_PIN    1    // Digital IO pin connected to the button.      


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
const uint16_t drawingColors[] = { GREEN, BLUE, CYAN, RED, YELLOW, PINK };

// Variables
int    x_size  = matrix.width();   // overall display matrix width
int    y_size  = matrix.height();  // overall display matrix height
int    x_pos   = matrix.width();   // track where we are in the scrolling message display
int    brightness = 10;            // set initial brightness of lights


// Button variables
bool oldState = HIGH;
int showType = 0;


void setup() {
  Serial.begin(9600);             // I dont know what this does
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  matrix.setTextColor(drawingColors[0]);
  Serial.println("NeoMatrix pixel grid test");
  Serial.println((String)"Matrix Pixel Width x Height: " + x_size + " x " + y_size);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

void loop() {

  
  bool newState = digitalRead(BUTTON_PIN); //Get current button state
  if (newState == LOW && oldState == HIGH) { //Check if state change from high to low
    delay(20);     // Short delay to debounce button.
    newState = digitalRead(BUTTON_PIN); //checks if button is still low after debounce

    // This cycles through a method everytime the button is pressed. It allows for many different patterns
    if (newState == LOW) {
      showType++;
      if (showType > 7)
        showType=0;
      startShow(showType);
    }
  }
oldState = newState;  // Set the last button state to the old state.
}

// This method cycles through other methods with the push of a button
void startShow(int i) {
  switch(i){
    case 0: drawFace();    
            break;
    case 1: drawFace2(); 
            break;
    case 2: rain(RED);
            break;
    case 3: drawFace3(RED); 
            break;
    case 4: linewipe(PINK);
            break;
    case 5: clownFace(BLUE);
            break;
    case 6: halfAndHalf(CYAN);
            break;
    case 7: sadFace(RED);
            break;
  }
}



            
// Makes face of white square eyes and a blue circle mouth
void drawFace() {
  matrix.fillScreen(0);
    matrix.fillRect(2, 1, 4, 5, WHITE);
    matrix.fillRect(17, 1, 4, 5, WHITE);
    matrix.fillCircle(11, 8, 2, BLUE);
    matrix.show();
}


// Makes face with horizontal white rectangle eyes and pink triangle mouth
void drawFace2() {
  matrix.fillScreen(0);
    matrix.fillRect(2, 2, 6, 3, WHITE);
    matrix.fillRect(17, 2, 6, 3, WHITE);
    matrix.fillTriangle(12, 6, 9, 9, 15, 9, PINK);
    matrix.show();
}


//quickly draws a face without wipping the board
void drawFace3(uint32_t color){ 
    for (int i = 1; i < 5; i++){
    int mouthy = i + 9 ;
    matrix.drawLine(2, i, 6, i, color);
    matrix.drawLine(16, i, 20, i, color);
    matrix.show();
    delay(30);
    }
    matrix.drawPixel(13, 11, color);
    delay(20);
    matrix.show();
    matrix.drawLine(12,10,14,10,color);
    delay(20);
    matrix.show();
    matrix.drawLine(11,9,15,9,color);
    delay(20);
    matrix.show();
    matrix.drawLine(10,8,16,8,color);
    delay(20);
    matrix.show();
    matrix.drawLine(10,7,16,7,color);
    delay(20);
    matrix.show();
  }

// Fills the entire board with "rain" and leaves it WHITE
void rain(uint32_t color) {
  int rnd;
  int rnd2;
  int rnd3;
  rnd = random(0, 7);
  rnd2 = random(0, 7);
  rnd3 = random(0, 7);
 for (int i = 0; i < y_size+1; i++) {
    matrix.fillScreen(0);
    matrix.drawLine(0, 0, 0, i+rnd, WHITE);
    matrix.drawPixel(0, i+rnd, color);
    matrix.drawLine(1, 0, 1, i+rnd2, WHITE);
    matrix.drawPixel(1, i+rnd2, color);
    
    matrix.drawLine(2, 0, 2, i+rnd3, WHITE);
    matrix.drawPixel(2, i+rnd3, color);
    matrix.drawLine(3, 0, 3, i, WHITE);
    matrix.drawPixel(3, i, color);
    matrix.drawLine(4, 0, 4, i+rnd, WHITE);
    matrix.drawPixel(4, i+rnd, color);
    
    matrix.drawLine(5, 0, 5, i+rnd, WHITE);
    matrix.drawPixel(5, i+rnd, color);
    matrix.drawLine(6, 0, 6, i, WHITE);
    matrix.drawPixel(6, i, color);
    matrix.drawLine(7, 0, 7, i+rnd2, WHITE);
    matrix.drawPixel(7, i+rnd2, color);
    
    matrix.drawLine(8, 0, 8, i+rnd, WHITE);
    matrix.drawPixel(8, i+rnd, color);
    matrix.drawLine(9, 0, 9, i+rnd3, WHITE);
    matrix.drawPixel(9, i+rnd3, color);
    matrix.drawLine(10, 0, 10, i+rnd2, WHITE);
    matrix.drawPixel(10, i+rnd2, color);
    matrix.drawLine(11, 0, 11, i, WHITE);
    matrix.drawPixel(11, i, color);

    matrix.drawLine(12, 0, 12, i, WHITE);
    matrix.drawPixel(12, i, color);
    matrix.drawLine(13, 0, 13, i+rnd, WHITE);
    matrix.drawPixel(13, i+rnd, color);
    matrix.drawLine(14, 0, 14, i+rnd3, WHITE);
    matrix.drawPixel(14, i+rnd3, color);
    matrix.drawLine(15, 0, 15, i, WHITE);
    matrix.drawPixel(15, i, color);

    matrix.drawLine(16, 0, 16, i+rnd2, WHITE);
    matrix.drawPixel(16, i+rnd2, color);
    matrix.drawLine(17, 0, 17, i+rnd3, WHITE);
    matrix.drawPixel(17, i+rnd3, color);
    matrix.drawLine(18, 0, 18, i, WHITE);
    matrix.drawPixel(18, i, color);
    matrix.drawLine(19, 0, 19, i+rnd, WHITE);
    matrix.drawPixel(19, i+rnd, color);

    matrix.drawLine(20, 0, 20, i, WHITE);
    matrix.drawPixel(20, i, color);
    matrix.drawLine(21, 0, 21, i, WHITE);
    matrix.drawPixel(21, i, color);
    matrix.drawLine(22, 0, 22, i+rnd3, WHITE);
    matrix.drawPixel(22, i+rnd3, color);

    
    matrix.show();
    delay(90);
    }}

// Turn grid one color with lines left to right
void linewipe(uint32_t color){
  for (int i = 0; i < x_size; i++){
    matrix.drawLine(0,0,i,0,color);
    matrix.drawLine(22,1,22-i,1,color);
    
    matrix.drawLine(0,2,i,2,color);
    matrix.drawLine(22,3,22-i,3,color);
    
    matrix.drawLine(0,4,i,4,color);
    matrix.drawLine(22,5,22-i,5,color);
    
    matrix.drawLine(0,6,i,6,color);
    matrix.drawLine(22,7,22-i,7,color);

    matrix.drawLine(0,8,i,8,color);
    matrix.drawLine(22,9,22-i,9,color);

    matrix.drawLine(0,10,i,10,color);
    matrix.drawLine(22,11,22-i,11,color);

    matrix.drawLine(0,12,i,12,color);
    matrix.show();
    delay(50);
    }
  }



// fill in all lines one at a time horizontally with 3 rnd color pixals leading the way.
// I am trying to make this end with a push of a button, currently does not.
void chaserThree(){
  int rnd;
  bool newState = digitalRead(BUTTON_PIN); //Get current button state
    if (newState == LOW && oldState == HIGH) { //Check if state change from high to low
    newState = digitalRead(BUTTON_PIN); //checks if button is still low after debounce 
      for (int x = 0; x < 1; x--){
      for (int i = 0; i < y_size+1; i++) {
        rnd = random(0, 6);
          for (int j = 0; j < x_size+1; j++) {
            matrix.drawLine(0, i, j, i, WHITE);
            matrix.drawPixel(j, i, drawingColors[rnd]);
            matrix.drawPixel(j+1, i, drawingColors[rnd]);
            matrix.drawPixel(j+2, i, drawingColors[rnd]);
            matrix.show();
            delay(20);
              
      }
     }
    
    // This cycles through a method everytime the button is pressed. It allows for many different patterns
    if (newState == LOW) {
    break;
    }
    oldState = newState;
  }
 }
}

//Makes one part of the grid a color and the other white (kinda works more for a flashy display than true halfs)
void halfAndHalf(uint32_t color){
  for (int i = 0; i < x_size+1; i++) {
    matrix.drawLine(0, 0, i, 12, WHITE);
    for (int j = 0; j < y_size+1; j++) {
      matrix.drawPixel(i, j, color);
      matrix.show();
      delay(10);
  
  }}}

// Fades an angry face in the grid of chosen color
void clownFace(uint32_t color){
  matrix.drawPixel(17, 1, color);
  matrix.drawPixel(5, 1, color);
  matrix.show();
  delay(20);
  matrix.drawLine(4, 2, 6, 2, color);
  matrix.drawLine(16, 2, 18, 2, color);
  matrix.show();
  delay(20);
  matrix.drawLine(3, 3, 7, 3, color);
  matrix.drawLine(15, 3, 19, 3, color);
  matrix.show();
  delay(20);
  matrix.drawLine(4, 4, 6, 4, color);
  matrix.drawLine(16, 4, 18, 4, color);
  matrix.show();
  delay(20);
  matrix.drawPixel(17, 5, color);
  matrix.drawPixel(5, 5, color);
  matrix.show();
  delay(20);
  
  // making mouth
  int count = 1;
  matrix.drawLine(12, 11, 12, 11, color);
  for (int i = 10; i > 7; i--){
    matrix.drawLine(12+count, i, 12-count, i, color);
    matrix.drawLine(12+count, i, 12-count, i, color);
    matrix.show();
    delay(30);
    count ++;
    }
  }

void sadFace(uint32_t color){
  matrix.fillCircle(5, 3, 2, color);
  matrix.fillCircle(17, 3, 2, color);
  matrix.show();
  delay(50);
  matrix.fillCircle(5, 3, 1, WHITE);
  matrix.fillCircle(17, 3, 1, WHITE);
  matrix.show();
  delay(50);
  // Making Mouth 
  for (int i = 0; i < 4; i++){
    matrix.drawRect(8, 8, 8-i, 5-i, color);
    matrix.show();
    delay(50);
  }
  matrix.drawLine(9, 10, 14, 10, WHITE);
  matrix.show();

}
