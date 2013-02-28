/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for(int i=5;i<=11;i++){
    pinMode(i, OUTPUT);     
  }
}

void loop() {
  for(int i=5;i<=11;i++){
    digitalWrite(i, HIGH);   // set the LED on
    delay(50);              // wait for a second
    digitalWrite(i, LOW);    // set the LED off
    delay(50);              // wait for a second
  }
  for(int i=5;i<=11;i++){
    digitalWrite(i, HIGH);   // set the LED on
    delay(50);              // wait for a second
  }
  for(int i=5;i<=11;i++){
    digitalWrite(i, LOW);    // set the LED off
    delay(50);              // wait for a second
  }
}
