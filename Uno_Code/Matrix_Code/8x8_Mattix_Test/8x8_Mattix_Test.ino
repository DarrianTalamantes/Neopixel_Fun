// You must use Aurduino Uno and change serial port to use this
// sudo chmod a+rw /dev/ttyACM0
// sudo chmod a+rw /dev/ttyUSB0

// button part of this code can be found on adafruit project hub NeoPixel x Arduino x Button
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define dataPin 6
#define matrixWidth   8   
#define matrixHeight  8
#define BUTTON_PIN   2    // Digital IO pin connected to the button.      

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(matrixWidth, matrixHeight, dataPin,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
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

const uint16_t drawingColors[] = { GREEN, BLUE, CYAN, WHITE, RED, YELLOW, PINK };

// Variables
int    x_size  = matrix.width();   // overall display matrix width
int    y_size  = matrix.height();  // overall display matrix height
int    x_pos   = matrix.width();   // track where we are in the scrolling message display
int    brightness = 10;
int    numPixals = x_size * y_size;

// Button variables
bool oldState = HIGH;
int showType = 0;


void setup() {
  
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  
  // matrix.fillScreen(WHITE);       // clear display after each button press
  bool newState = digitalRead(BUTTON_PIN); //Get current button state
  if (newState == LOW && oldState == HIGH) { //Check if state change from high to low
    delay(20);     // Short delay to debounce button.
    newState = digitalRead(BUTTON_PIN); //checks if button is still low after debounce

    // This cycles through a method everytime the button is pressed. It allows for many different patterns
    if (newState == LOW) {
      showType++;
      if (showType > 6)
        showType=0;
      startShow(showType);
    }
  }
oldState = newState;  // Set the last button state to the old state.
}


// Method to cycle through other methods
void startShow(int i) {
  switch(i){
    case 0: colorWipeDown(GREEN, 50);    // Turns all pixels green
            break;
    case 1: linewipe(PINK); //Turns all pixels Pink
            break;
    case 2: colorWipeDown(BLUE, 50); //Turns all pixels Blue
            break;
    case 3: colorWipeRight(RED, 50);  //Turns all Pixels Red
            break;
    case 4: drawRectangles();
            break;
    case 5: rain();
            break;
    case 6: linewipe(RED);
            break;
  }
}


  
// Make every pixal in the matrix the same color from top to bottom
void colorWipeDown(uint32_t color, int wait) {
  for(int i=0; i<x_size; i++) { 
    for(int j=0; j<y_size; j++){
      matrix.drawPixel(i,j,color);
      matrix.show();
    }
    delay(wait);                           //  Pause for a moment
  }
}

// Make every pixal in the matrix the same color from left to right
void colorWipeRight(uint32_t color, int wait) {
  for(int i=0; i<x_size; i++) { 
    for(int j=0; j<y_size; j++){
      matrix.drawPixel(j,i,color);
      matrix.show();
    }
    delay(wait);                           //  Pause for a moment
  }
}

// Makes many rectangles
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

// Turn grid one color with lines left to right
void linewipe(uint32_t color){
  for (int i = 0; i < x_size; i++){
    matrix.drawLine(0,0,i,0,color);
    matrix.drawLine(7,1,7-i,1,color);
    
    matrix.drawLine(0,2,i,2,color);
    matrix.drawLine(7,3,7-i,3,color);
    
    matrix.drawLine(0,4,i,4,color);
    matrix.drawLine(7,5,7-i,5,color);
    
    matrix.drawLine(0,6,i,6,color);
    matrix.drawLine(7,7,7-i,7,color);
    matrix.show();
    delay(100);
    }
  }







// 
void rain(){
 for (int i = 0; i < y_size; i++) {
    matrix.fillScreen(0);
    matrix.drawLine(0, 0, 0, i, WHITE);
    matrix.drawPixel(0, i, BLUE);
    matrix.show();
    delay(80);
    }
}
