#include "SPI.h"
#include "Adafruit_WS2801.h"
int debug = 0;
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
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 * 
 *****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(20, dataPin, clockPin, WS2801_GRB);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {
  4, 5, 6}; // the analog 0-5 pins are also known as 14-19
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

boolean pin13state = false;
byte lightMode = 0;
unsigned long startTime = millis();
byte numberOfModes = 6;

void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  Serial.begin(9600);
  Serial.println("Rainbow and rainbow cycle with time decaying maximum intensity and button detection");
  // Make input & enable pull-up resistors on switch pins
  for (byte i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
    Serial.println("Setting button to input");
  }
}


void loop() {
  // Some example procedures showing how to display to the pixels
  pin13state = !pin13state;
  digitalWrite(13, pin13state);


  if(lightMode == 0){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Rainbow");
    rainbow(50);
  }
  if(lightMode == 1){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Rainbow Cycle");
    rainbowCycle(50);
  }
  //  if(lightMode == 2){
  //    Serial.println("Mode two: Color Wipes");
  //    colorWipes(150);
  //  }
  if(lightMode == 2){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Red");
    byte r=255;
    colorWipe(Color(r, 0, 0), 100);
  }
  if(lightMode == 3){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Green");
    for (int i=0; i < strip.numPixels(); i++) {
      byte r = random(20);
      byte g = 255;
      byte b = random(20);
      strip.setPixelColor(i, Color(r, g, b));
      strip.show();
      delay(100);
      if(detect_modechange()){
        break;
      }
    }
  }
  if(lightMode == 4){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Blue");
    for (int i=0; i < strip.numPixels(); i++) {
      byte r = random(20);
      byte g = random(20);
      byte b = 255;
      strip.setPixelColor(i, Color(r, g, b));
      strip.show();
      delay(100);
      if(detect_modechange()){
        break;
      }
    }
  }
  if(lightMode == 5){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Red+Blue");
    for (int i=0; i < strip.numPixels(); i++) {
      byte r = 255;
      byte g = random(20);
      byte b = 255;
      strip.setPixelColor(i, Color(r, g, b));
      strip.show();
      delay(100);
      if(detect_modechange()){
        break;
      }
    }
  }
  if(lightMode == 6){
    Serial.print("Mode ");
    Serial.print(lightMode);
    Serial.println(": Red+Blue+Green");
    colorWipe(Color(255, 255, 255), 100);
  }
  //rainbow(50);
  //rainbowCycle(50);
}

void readbuttons(){
  // need to rewrite this to use another variable rather than using a delay to debounce
  for(int pin = 4;pin <=6;pin++){
    if(digitalRead(pin) != buttons[pin]){
      delay(5); // debounce
      if(digitalRead(pin) != buttons[pin]){
        buttons[pin] =  !buttons[pin];
      }
    }
  }
}

void rainbow(uint8_t wait) {
  int i, j;

  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
    if(detect_modechange()){
      return;
    }
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
    if(detect_modechange()){
      return;
    }
  }
}

void colorWipes(uint8_t wait){
  for(byte r=0;r<256;r++){
    colorWipe(Color(r, 0, 0), wait);
    if(detect_modechange()){
      return;
    }
  }
  for(byte g=0;g<256;g++){
    colorWipe(Color(0, g, 0), wait);
    if(detect_modechange()){
      return;
    }
  }
  for(byte b=0;b<256;b++){
    colorWipe(Color(0, 0, b), wait);
    if(detect_modechange()){
      return;
    }
  }
}
// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    if(detect_modechange()){
      return;
    }
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{

  int maxintensity = getmaxintensity();
  //Serial.print("millis is ");
  //Serial.println(millis());
  //Serial.print("maxintensity is ");
  //Serial.println(maxintensity);
  r = (r > maxintensity) ? maxintensity : r;
  g = (g > maxintensity) ? maxintensity : g;
  b = (b > maxintensity) ? maxintensity : b;
  if(debug >1){
    Serial.print("RGB = ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print(b);
    Serial.println(" ");
  }

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

int getmaxintensity (void){
  long time = (millis() - startTime) / 1000; //Seconds
  if(time < 600){ //first 10 minutes fade from 255 to 50
    return int((-0.341 * time) + 255);
  }
  else if(time < 1200){ //second 10 minutes fade from 50 to 10
    return int((-0.0667 * time) + 90);
  }
  else if(time < 1800){ //third 10 minutes fade from 10 to zero
    return int((-0.0167 * time) + 30);
  }
  else if(time < 2400){
    return 1;
  }
  else{
    return 0;
  }
}

void check_switches()
{
  //Serial.println("Checking switches");
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  static long lasttime;
  byte index;

  if (millis() < lasttime) {
    // we wrapped around, lets just try again
    lasttime = millis();
  }

  if ((lasttime + DEBOUNCE) > millis()) {
    // not enough time has passed to debounce
    return; 
  }
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lasttime = millis();

  for (index = 0; index < NUMBUTTONS; index++) {
    justpressed[index] = 0;       // when we start, we clear out the "just" indicators
    justreleased[index] = 0;

    currentstate[index] = digitalRead(buttons[index]);   // read the button


    //Serial.print(index, DEC);
    //Serial.print(": cstate=");
    //Serial.print(currentstate[index], DEC);
    //Serial.print(", pstate=");
    //Serial.print(previousstate[index], DEC);
    //Serial.print(", press=");


    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
        // just pressed
        justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
        // just released
        justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}

byte detect_modechange(){
  //Serial.println("Checking for mode change");
  byte modeChange = 0;
  check_switches();
  if(justpressed[0]){
    modeChange++;
    lightMode++;
    if(lightMode > numberOfModes){
      lightMode = 0;
    }
  }
  if(justpressed[1]){
    startTime = millis();
  }
  if(justpressed[2]){
    startTime -= 600000; // Advance the clock 10 minutes
  }
  if(modeChange){
    Serial.print("Mode changed to ");
    Serial.println(lightMode);
  }
  return modeChange;
}


















