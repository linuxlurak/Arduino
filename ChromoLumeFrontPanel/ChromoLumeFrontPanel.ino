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
int signalToDisc = 4;
// Pin 5 = Panel voltmeter 1
// Pin 6 = Panel voltmeter 2
int resetSwitch = 8;
int redPin = 9; // Output pins for connection to analog LED strip
int greenPin = 10;
int bluePin = 11;
int modeSwitch = 12;

boolean standby = true;
boolean resetFlag = false;

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels in a row and
// the second value to number of pixels in a column.
Adafruit_WS2801 strip = Adafruit_WS2801((uint16_t)4, (uint16_t)5, dataPin, clockPin, WS2801_GRB);

void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  pinMode(signalToDisc, OUTPUT);
  digitalWrite(signalToDisc, LOW);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(7, INPUT);
  pinMode(resetSwitch, INPUT);
  pinMode(modeSwitch, INPUT);
  digitalWrite(7, HIGH);
  digitalWrite(resetSwitch, HIGH);
  digitalWrite(modeSwitch, HIGH);
}


void loop() {
  Serial.println("Top of Loop");
  digitalWrite(signalToDisc, LOW);
  resetFlag = false;
  idleMode();
  preActivation();
  breakdown();
  preActivation();
  showtime();

}

void preActivation(void){
  if(resetFlag == true){
    return;
  }
  Serial.println("Preactivation mode");
  digitalWrite(signalToDisc, HIGH);
  delay(40);
  digitalWrite(signalToDisc, LOW);
  while(1){
    if(digitalRead(modeSwitch)==LOW){
      delay(10);
      if(digitalRead(modeSwitch)==LOW){
        while(digitalRead(modeSwitch)==LOW){
        }
        return;
      }
    }
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
  }
}

void breakdown(void){
  if(resetFlag == true){
    return;
  }
  Serial.println("Breakdown");
  digitalWrite(signalToDisc, HIGH);
  delay(40);
  digitalWrite(signalToDisc, LOW);

  analogWrite(5, 0);
  analogWrite(6, 0);
  for(int i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,Color(0,0,0));
  }
  strip.show();
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(500);

  while(1){
    if(digitalRead(modeSwitch)==LOW){
      delay(10);
      if(digitalRead(modeSwitch)==LOW){
        while(digitalRead(modeSwitch)==LOW){
        }
        return;
      }
    }
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
  }
}

void idleMode(){
  if(resetFlag == true){
    return;
  }
  Serial.println("idleMode");
  char message[90];
  int pin5 = 30;
  int pin5change = 1;
  int pin6 = 255;
  int pin6change = -1;
  int red=0;
  int redchange = 1;
  long wheelPos = 0;
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);


  while(1){
    long iterationCount = 0;
    analogWrite(5, pin5);
    analogWrite(6, pin6);
    sprintf(message, "pin5=%03d, pin6=%03d", pin5, pin6);
    //Serial.println(message);
    pin5 = pin5 + pin5change;
    pin6 = pin6 + pin6change;
    if(pin5 > 254){
      pin5change = -1;
    }
    else if(pin5 < 30){
      pin5change = 1;
    }
    if(pin6 > 254){
      pin6change = -1;
    }
    else if(pin6 < 30){
      pin6change = 1;
    }

    if(1){ // making this always true for now
      for(int i=0;i<strip.numPixels();i++){
        strip.setPixelColor(i,Color(red,0,0));
        sprintf(message, "Pixel: %03d is red: %03d, Color is %d", i, red, Color(red,0,0));
        //Serial.println(message);
      }
      strip.show();

      red = red + redchange;
      if(red > 30){
        redchange = -1;
      }
      else if (red < 20){
        redchange = 1;
      }
    }
    analogWrite(redPin, WheelRed(wheelPos));
    analogWrite(greenPin, WheelGreen(wheelPos));
    analogWrite(bluePin, WheelBlue(wheelPos));
    wheelPos++;
    //changeStriplight();
    if(digitalRead(7)==LOW){
      return;
    }
    if(digitalRead(8)==LOW){
      return;
    }
    if(digitalRead(modeSwitch)==LOW){
      while(digitalRead(modeSwitch)==LOW){
      }
      return;
    }
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
    delay(250);
  }
}

void showtime(void){
  if(resetFlag == true){
    return;
  }
  Serial.println("Showtime!!!!");
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
  if(digitalRead(resetSwitch) == LOW){
    delay(10);
    if(digitalRead(resetSwitch) == LOW){
      while(digitalRead(resetSwitch) == LOW){
      }
      resetFlag = true;
      return;
    }
  }
}

void randomAnalogPins(void){
  if(resetFlag == true){
    return;
  }
  analogWrite(5,random(40,255));
  analogWrite(6,random(40,255));
}

void changeStriplight(void){
  static int red=0;
  static int green=0;
  static int blue=0;
  static int rTarget = random(255);
  static int gTarget = random(255);
  static int bTarget = random(255);

  if(red == rTarget && green == gTarget && blue == bTarget){
    gTarget = random(255);
    bTarget = random(255);
    long gplusb = gTarget + bTarget;
    long fiveTenMinusgplusb = 510 - gplusb;
    rTarget = random(min(255,fiveTenMinusgplusb));
    char targetMsg[90];
    sprintf(targetMsg, "rTarget: %03d, gTarget: %03d, bTarget: %03d", rTarget, gTarget, bTarget);
    Serial.println(targetMsg);
  }
  red = convergeColorValue(red, rTarget);
  green = convergeColorValue(green, gTarget);
  blue = convergeColorValue(blue, bTarget);
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  //Serial.print(".");
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
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
    if(resetFlag == true){
      return;
    }
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
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
    if(resetFlag == true){
      return;
    }
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
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
    if(resetFlag == true){
      return;
    }
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
    if(digitalRead(resetSwitch) == LOW){
      delay(10);
      if(digitalRead(resetSwitch) == LOW){
        while(digitalRead(resetSwitch) == LOW){
        }
        resetFlag = true;
        return;
      }
    }
    if(resetFlag == true){
      return;
    }
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
  char message[90];
  sprintf(message, "In Color function, red is %d, green is %d, blue is %d", r, g, b);
  //Serial.println(message);
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  //Serial.println(c, HEX);
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

int WheelRed(byte WheelPos)
{
  if (WheelPos < 85) {
    return (WheelPos * 3);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return (255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return 0;
  }
}

int WheelGreen(byte WheelPos)
{
  if (WheelPos < 85) {
    return (255 - WheelPos * 3);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return 0;
  } 
  else {
    WheelPos -= 170; 
    return (WheelPos * 3);
  }
}

int WheelBlue(byte WheelPos)
{
  if (WheelPos < 85) {
    return 0;
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return (WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return (255 - WheelPos * 3);
  }
}














