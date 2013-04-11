#include <Adafruit_NeoPixel.h>
#include <Sleep.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  for(int i=255;i>0;i--){
    Serial.println(i);
    int pixdelay;
    if(i>150){
      pixdelay = 30;
    }
    else if(i>70){ //50
      if(i == 150){
        Serial.print(millis()/60000);
        Serial.println(" Minutes");
      }
      pixdelay = 80; //60
    }
    else{
      if(i == 70){
        Serial.print(millis()/60000);
        Serial.println(" Minutes");
      }
      pixdelay = 200; //150
    }
    colorWipe(strip.Color(i, random(0,int(i/10)),random(0,int(i/10))), pixdelay); // Red
  }
  Serial.print(millis()/60000);
  Serial.println(" Minutes");
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(random(0,4),random(0,4),random(0,4)));
    strip.show();
    delay(4000);
  }
  Serial.print(millis()/60000);
  Serial.println(" Minutes");
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(1,0,0));
    strip.show();
    delay(4000);
  }
  Serial.print(millis()/60000);
  Serial.println(" Minutes");
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(0,0,0));
    strip.show();
    delay(4000);
  }
  Serial.print(millis()/60000);
  Serial.println(" Minutes");
  Serial.println("Good night! :-)");
  while(1){
    delay(10000);
  }
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //rainbow(20);
  //rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



