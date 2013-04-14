#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
 * Example sketch for driving Adafruit WS2801 pixels!
 * 
 * 
 * Designed specifically to work with the Adafruit RGB Pixels!
 * 12mm Bullet shape ----> https://www.adafruit.com/products/322
 * 12mm Flat shape   ----> https://www.adafruit.com/products/738
 * 36mm Square shape ----> https://www.adafruit.com/products/683
 * 
 * These pixels use SPI to transmit the color data, and have built in
 * high speed PWM drivers for 24 bit color per pixel
 * 2 pins are required to interface
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by David Kavanagh (dkavanagh@gmail.com).  
 * BSD license, all text above must be included in any redistribution
 * 
 *****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Pin 5 = Panel voltmeter 1
// Pin 6 = Panel voltmeter 2
int redPin = 9; // Output pins for connection to analog LED strip
int greenPin = 10;
int bluePin = 11;

boolean standby = true;
// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels in a row and
// the second value to number of pixels in a column.
Adafruit_WS2801 strip = Adafruit_WS2801((uint16_t)4, (uint16_t)5, dataPin, clockPin);

void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


void loop() {
  Serial.println("");
  Serial.println("Top of Loop");
  // Some example procedures showing how to display to the pixels
  //drawX(4, 4, 100);
  //bounce(4, 5, 50);

  randomAnalogPins();
  for(int count=random(20);count>=0;count--){
    rollUp(random(255),random(255),random(255),random(250));
  }
  randomAnalogPins();
  for(int count=random(20);count>=0;count--){
    rollDown(random(255),random(255),random(255),random(250));
  }
  randomAnalogPins();
  for(int count=random(20);count>=0;count--){
    rollRight(random(255),random(255),random(255),random(250));
  }
  randomAnalogPins();
  for(int count=random(20);count>=0;count--){
    rollLeft(random(255),random(255),random(255),random(250));
  }
  randomAnalogPins();
}

void randomAnalogPins(void){
    analogWrite(5,random(40,255));
    analogWrite(6,random(40,255));
}

void changeStriplight(void){
  static int red=255;
  static int green=255;
  static int blue=255;
  static int rTarget = random(255);
  static int gTarget = random(255);
  static int bTarget = random(255);
  
  if(red == rTarget && green == gTarget && blue == bTarget){
    rTarget = random(255);
    gTarget = random(255);
    bTarget = random(255);
    Serial.println("");
    Serial.print("new target: ");
  }
  red = convergeColorValue(red, rTarget);
  green = convergeColorValue(green, gTarget);
  blue = convergeColorValue(blue, bTarget);
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  Serial.print(".");
}

int convergeColorValue(int current, int target){
  if(current<target){
    current++;
  }
  else if(current>target){
    current--;
  }
  if(standby == false){ // if we have exited standby mode, add an extra increment/decrement to move us towards target faster
    if(current<target){
      current++;
    }
    else if(current>target){
      current--;
    }
  }
  return current;
}

void rollRight(int r, int g, int b, long wait) {
  for (int x=0;x<4;x++) {
    changeStriplight();
    for (int y=0;y<5;y++){
      strip.setPixelColor(x,y,r,g,b);
    }
    strip.show();
    delay(wait);
    for(int y=0;y<5;y++){
      strip.setPixelColor(x,y,random(20),random(20),random(20));
    }
    strip.show();
  }
}
void rollLeft(int r, int g, int b, long wait) {
  for (int x=3;x>=0;x--) {
    changeStriplight();
    for (int y=0;y<5;y++){
      strip.setPixelColor(x,y,r,g,b);
    }
    strip.show();
    delay(wait);
    for(int y=0;y<5;y++){
      strip.setPixelColor(x,y,random(20),random(20),random(20));
    }
    strip.show();
  }
}
void rollUp(int r, int g, int b, long wait) {
  for (int y=4;y>=0;y--) {
    changeStriplight();
    for (int x=0;x<5;x++){
      strip.setPixelColor(x,y,r,g,b);
    }
    strip.show();
    delay(wait);
    for(int x=0;x<5;x++){
      strip.setPixelColor(x,y,random(20),random(20),random(20));
    }
    strip.show();
  }
}
void rollDown(int r, int g, int b, long wait) {
  for (int y=0;y<5;y++) {
    changeStriplight();
    for (int x=0;x<5;x++){
      strip.setPixelColor(x,y,r,g,b);
    }
    strip.show();
    delay(wait);
    for(int x=0;x<5;x++){
      strip.setPixelColor(x,y,random(20),random(20),random(20));
    }
    strip.show();
  }
}
void drawX(uint8_t w, uint8_t h, uint8_t wait) {
  uint16_t x, y;
  for (x=0; x<w; x++) {
    strip.setPixelColor(x, x, 255, 0, 0);
    strip.show();
    delay(wait);
  }
  for (y=0; y<h; y++) {
    strip.setPixelColor(w-1-y, y, 0, 0, 255);
    strip.show();
    delay(wait);
  }

}

void bounce(uint8_t w, uint8_t h, uint8_t wait) {
  int16_t x = 1;
  int16_t y = 2;
  int8_t xdir = +1;
  int8_t ydir = -1;
  int j;
  for (j=0; j < 256; j++) {
    x = x + xdir;
    y = y + ydir;
    if (x < 0) {
      x = -x;
      xdir = - xdir;
    }
    if (y < 0) {
      y = -y;
      ydir = - ydir;
    }
    if (x == w) {
      x = w-2;
      xdir = - xdir;
    }
    if (y == h) {
      y = h-2;
      ydir = - ydir;
    }
    strip.setPixelColor(x, y, Wheel(j));
    strip.show();
    delay(wait);
    strip.setPixelColor(x, y, 0, 0, 0);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

