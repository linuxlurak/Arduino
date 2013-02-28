// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11
 
#define FADESPEED 45     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(2, INPUT);
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  for (int l = 0; l < 256; l++){
    analogWrite(REDPIN, l);
    analogWrite(GREENPIN, l);
    analogWrite(BLUEPIN, l);
    delay(FADESPEED);
  }
}
 
 
void loop() {
  int l, r, g, b;

  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
}

void waitForInput(){
  int flag = 0;
  /*
  while(!flag){
    flag = digitalRead(2);
  }
  */
}
