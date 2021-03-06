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
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

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

void setup() {
  randomSeed(1);
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels

  pulsation();
}

void pulsation(void){
  int interdelay = 10;
  int threshold = 100;
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,0,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,0,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(0,color,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(0,color,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(0,0,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(0,0,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,0,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,0,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,color,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,color,0));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=0;color<256;color++){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,color,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
  }
  for(int color=255;color>=0;color--){
    for(int pixel=0;pixel<strip.numPixels();pixel++){
      strip.setPixelColor(pixel, Color(color,color,color));
    }
    strip.show();
    if(color<threshold){delay(interdelay*(threshold-color));}
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




