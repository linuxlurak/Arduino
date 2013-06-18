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

// DEFINES
#define REDDISH 0
#define GREENISH 1
#define BLUEISH 2
#define RAINBOW 3
#define THIRTYMINUTES 1800000
#define REDBUTTON 0
#define GREENBUTTON 1
#define BLUEBUTTON 2
#define YELLOWBUTTON 3
#define GRAYTOPBUTTON 4
#define GRAYBOTTOMBUTTON 5
#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty
#define RETRIGGERDELAY 500 // ms delay between between repeating the same action on button held down or consecutive presses

// GLOBALS
volatile byte intensity = 255;
volatile byte mode = REDDISH;
volatile byte rainbowSubmode = 0;
volatile unsigned long thirtyMinuteStart = 0;
unsigned int pixdelay;
long lastDecrementTime = 0;

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {
  0, 1, 2, 3, 4, 5}; // the analog 0-5 pins are also known as 14-19
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
long needsAttention[NUMBUTTONS]; // Records the value of millis() any time that we check buttons and find that a button was currently pressed
// needsAttention[] will record a non-zero value if the button has been pressed even if it isn't anymore
// Any code that takes action on a button press should reset the corresponding element of needsAttention[] to zero after taking
// the appropriate action that the button is supposed to cause

void setup() {
  //  delay(5000);
  Serial.println("Starting up");
  //  delay(5000);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  // Make input & enable pull-up resistors on switch pins
  for (byte i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
    needsAttention[i] = 0;
  }

  mode = REDDISH;
}

void loop() {
  //  Serial.println("");
  Serial.println("Top of loop");
  if(intensity == 0){
    printUptime();
    shuttingDown();
    Serial.println("Good night! :-)");
    while(intensity == 0){
      idelay(1000);
    }
  }
  if(thirtyMinuteStart == 0 || (millis() - thirtyMinuteStart) > THIRTYMINUTES){
    if((millis() - lastDecrementTime) > RETRIGGERDELAY){
      intensity--;
      lastDecrementTime = millis();
    }
  }
  if(intensity > 0){
    pixdelay = int(intensity * (-2.0/3.0) + 200);
    printUptime();
    doModeAction();
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
      Serial.println("Randomize Pixels");
      randomizePixels(intensity, pixdelay);
    }
    else if(rainbowSubmode == 1){
      Serial.println("Rainbow");
      rainbow(pixdelay);
    }
    else if(rainbowSubmode == 2){
      Serial.println("Rainbow Cycle");
      rainbowCycle(pixdelay);
    }
  }
}

void randomizePixels(byte maxintensity, unsigned long wait){
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(random(0,maxintensity),random(0,maxintensity),random(0,maxintensity)));
    strip.show();
    Serial.print(".");
    if(idelay(wait)){
      return;
    }
  }
}

void shuttingDown(void){
  Serial.println("Beginning shutdown display");
  randomizePixels(4,4000);
  printUptime();
  if(intensity > 0){
    return;
  }
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(1,0,0));
    strip.show();
    if(idelay(4000) && intensity > 0){
      return;
    }
  }
  if(intensity > 0){
    return;
  }
  printUptime();
  for(int pixel=0;pixel<strip.numPixels();pixel++){
    strip.setPixelColor(pixel, strip.Color(0,0,0));
    strip.show();
    if(idelay(4000) && intensity > 0){
      return;
    }
  }
  printUptime();
}

void printUptime(void){
  //  return;
  //  if(intensity % 25 == 0){
  Serial.println("");
  Serial.print("Intensity: ");
  Serial.print(intensity);
  Serial.print("   Extratime: ");
  if(thirtyMinuteStart == 0){
    Serial.print("0");
  }
  else if((millis() - thirtyMinuteStart) < THIRTYMINUTES){
    Serial.print((THIRTYMINUTES - (millis() - thirtyMinuteStart))/1000);
  }
  else{
    Serial.print("0");
  }
  Serial.print(" seconds   Pixdelay:");
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
    if(idelay(wait)){
      return;
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    Serial.print(".");
    if(idelay(wait * (strip.numPixels()/256.0))){ //Compensate for 256 delays vs numPixels delays in the wipes
      return;
    }
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
    Serial.print(".");
    if(idelay(wait * (strip.numPixels() / ( 256.0 * 5.0)))){ // Compensate for 256*5 delays vs numPixels delays in the wipes
      return;
    }
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
  static long triggered = 0;
  if(millis() - triggered < RETRIGGERDELAY){
    // Don't retrigger too quickly. We want humanly distinct button presses
    return;
  }
  triggered = millis();
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
  static long triggered = 0;
  if(millis() - triggered < RETRIGGERDELAY){
    // Don't retrigger too quickly. We want humanly distinct button presses
    return;
  }
  triggered = millis();
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
  static long triggered = 0;
  if(millis() - triggered < RETRIGGERDELAY){
    // Don't retrigger too quickly. We want humanly distinct button presses
    return;
  }
  triggered = millis();
  thirtyMinuteStart = 0;
  if(intensity > 9){
    intensity -= 10;
  }
  else{
    intensity = 0;
  }
}

void check_buttons()
{
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

    /*     
     Serial.print(index, DEC);
     Serial.print(": cstate=");
     Serial.print(currentstate[index], DEC);
     Serial.print(", pstate=");
     Serial.print(previousstate[index], DEC);
     Serial.print(", press=");
     */

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
      if(pressed[index] == HIGH){
        needsAttention[index] = lasttime; //record the last time the button was pressed
      }
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}

int idelay(long targetDelay){
  // A drop in replacement for delay(). This one keeps checking switches rather than doing nothing.
  long delayStart = millis();
  int handleResponse = 0;
  while(millis() - delayStart < targetDelay){
    check_buttons();
    handleResponse = handle_buttons();
    if(handleResponse){
      break;
    }
  }
  return handleResponse;
}

int handle_buttons(void){
  // iterate over the buttons arrays and take any necessary actions on buttons that are/were pressed
  int buttonsHandled = 0;
  if(needsAttention[REDBUTTON]){
    redButtonISR();
    needsAttention[REDBUTTON] = 0;
    buttonsHandled++;
  }
  if(needsAttention[GREENBUTTON]){
    greenButtonISR();
    needsAttention[GREENBUTTON] = 0;
    buttonsHandled++;
  }
  if(needsAttention[BLUEBUTTON]){
    blueButtonISR();
    needsAttention[BLUEBUTTON] = 0;
    buttonsHandled++;
  }
  if(needsAttention[YELLOWBUTTON]){
    yellowButtonISR();
    needsAttention[YELLOWBUTTON] = 0;
    buttonsHandled++;
  }
  if(needsAttention[GRAYTOPBUTTON]){
    grayTopButtonISR();
    needsAttention[GRAYTOPBUTTON] = 0;
    buttonsHandled++;
  }
  if(needsAttention[GRAYBOTTOMBUTTON]){
    grayBottomButtonISR();
    needsAttention[GRAYBOTTOMBUTTON] = 0;
    buttonsHandled++;
  }
  return buttonsHandled;
}






