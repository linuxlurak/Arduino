#include <Adafruit_NeoPixel.h>
#include <Sleep.h>
//#include <PinChangeInt.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);

// DEFINES
#define REDDISH 0
#define GREENISH 1
#define BLUEISH 2
#define RAINBOW 3
#define THIRTYMINUTES 30 * 60 * 1000
#define REDBUTTON 0
#define GREENBUTTON 1
#define BLUEBUTTON 2
#define YELLOWBUTTON 3
#define GRAYTOPBUTTON 4
#define GRAYBOTTOMBUTTON 5


// GLOBALS
volatile byte intensity = 255;
volatile byte mode = REDDISH;
volatile byte rainbowSubmode = 0;
volatile unsigned long thirtyMinuteStart = 0;
unsigned int pixdelay;

void setup() {
  delay(5000);
  Serial.println("Starting up");
  delay(5000);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(REDBUTTON, INPUT);
  digitalWrite(REDBUTTON, HIGH);
  attachInterrupt(0, redButtonISR, FALLING);
//  PCintPort::attachInterrupt(REDBUTTON, &redButtonISR, FALLING);
  pinMode(GREENBUTTON, INPUT);
  digitalWrite(GREENBUTTON, HIGH);
    attachInterrupt(1, greenButtonISR, FALLING);
//  PCintPort::attachInterrupt(GREENBUTTON, &greenButtonISR, FALLING);
  pinMode(BLUEBUTTON, INPUT);
  digitalWrite(BLUEBUTTON, HIGH);
    attachInterrupt(2, blueButtonISR, FALLING);
//  PCintPort::attachInterrupt(BLUEBUTTON, &blueButtonISR, FALLING);
  pinMode(YELLOWBUTTON, INPUT);
  digitalWrite(YELLOWBUTTON, HIGH);
    attachInterrupt(3, yellowButtonISR, FALLING);
//  PCintPort::attachInterrupt(YELLOWBUTTON, &yellowButtonISR, FALLING);
  pinMode(GRAYTOPBUTTON, INPUT);
  digitalWrite(GRAYTOPBUTTON, HIGH);
//  PCintPort::attachInterrupt(GRAYTOPBUTTON, &grayTopButtonISR, FALLING);
  pinMode(GRAYBOTTOMBUTTON, INPUT);
  digitalWrite(GRAYBOTTOMBUTTON, HIGH);
//  PCintPort::attachInterrupt(GRAYBOTTOMBUTTON, &grayBottomButtonISR, FALLING);
}

void loop() {
  Serial.println("");
  Serial.println("Top of loop");
  if(thirtyMinuteStart == 0 || (millis() - thirtyMinuteStart) > THIRTYMINUTES){
    intensity--;
  }
  if(intensity > 0){
    pixdelay = int(intensity * (-2.0/3.0) + 200);
    printUptime();
    doModeAction();
  }
  else{
    printUptime();
    shuttingDown();
    Serial.println("Good night! :-)");
    while(1){
      delay(10000);
    }
  }
}

void doModeAction(void){
  if(mode == REDDISH){
    Serial.println("REDDISH colorWipe");
    colorWipe(strip.Color(intensity, random(0,int(intensity/10)),random(0,int(intensity/10))), pixdelay); // Red
  }
  else if(mode == GREENISH){
    Serial.println("GREENISH colorWipe");
    colorWipe(strip.Color(random(0,int(intensity/10)), intensity, random(0,int(intensity/10))), pixdelay); // Green
  }
  else if(mode == BLUEISH){
    Serial.println("BLUEISH colorWipe");
    colorWipe(strip.Color(random(0,int(intensity/10)),random(0,int(intensity/10)),intensity), pixdelay); // Blue
  }
  else if(mode == RAINBOW){
    if(rainbowSubmode == 0){
      Serial.println("randomize pixels");
      randomizePixels(intensity, pixdelay);
    }
    else if(rainbowSubmode == 1){
      Serial.println("rainbow");
      rainbow(pixdelay);
    }
    else if(rainbowSubmode == 2){
      Serial.println("rainbow cycle");
      rainbowCycle(pixdelay);
    }
  }
}

void randomizePixels(byte maxintensity, unsigned long wait){
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(random(0,maxintensity),random(0,maxintensity),random(0,maxintensity)));
    strip.show();
    delay(wait);
  }
}

void shuttingDown(void){
  Serial.println("Beginning shutdown display");
  randomizePixels(4,4000);
  printUptime();
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(1,0,0));
    strip.show();
    delay(4000);
  }
  printUptime();
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(0,0,0));
    strip.show();
    delay(4000);
  }
  printUptime();
}

void printUptime(void){
  //  if(intensity % 25 == 0){
  Serial.println("");
  Serial.print("Intensity: ");
  Serial.print(intensity);
  Serial.print("   Pixdelay:");
  Serial.print(pixdelay);
  Serial.print("   ");
  Serial.print(millis()/60000);
  Serial.print(" Minutes    Mode:");
  Serial.print(mode);
  Serial.print(" Rainbow submode: ");
  Serial.println(rainbowSubmode);
  //  }
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    Serial.print(".");
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
    return strip.Color(min(intensity, WheelPos * 3), min(intensity, 255 - WheelPos * 3), 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(min(intensity, 255 - WheelPos * 3), 0, min(intensity, WheelPos * 3));
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, min(intensity, WheelPos * 3), min(intensity, 255 - WheelPos * 3));
  }
}

void redButtonISR(void){
  mode = REDDISH;
}

void greenButtonISR(void){
  mode = GREENISH;
}

void blueButtonISR(void){
  mode = BLUEISH;
}

void yellowButtonISR(void){
  if(mode == RAINBOW){
    //Serial.print("Rainbow submode was: ");
    //Serial.print(rainbowSubmode);
    rainbowSubmode = (rainbowSubmode + 1) % 3;
    //Serial.print(" Rainbow submode now is: ");
    //Serial.println(rainbowSubmode);
  }
  else{
    mode = RAINBOW;
  }
}

void grayTopButtonISR(void){
  if(intensity == 0){
    intensity = 255;
  }
  else if(intensity < 246){
    intensity += 10;
  }
  else{
    intensity = 255;
    thirtyMinuteStart = millis();
  }
}

void grayBottomButtonISR(void){
  if(intensity > 9){
    intensity -= 10;
  }
  else{
    intensity = 0;
  }
}






