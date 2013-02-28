/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
//  Serial.begin(9600);
}


void loop() {
  //Serial.println("Main Loop Begin");
  int i=0;
  while(i < 10){
    //Serial.print("While loop begin i=");
    //Serial.println(i);
    //delay(1000);
//    digitalWrite(13, HIGH);   // set the LED on
//    delay(i * 1000);              // wait for a second
//    digitalWrite(13, LOW);    // set the LED off
//    delay(i * 1000);              // wait for a second
    count(i);
    i++;
    //digitalWrite(13, LOW);
    //Serial.println("While loop end");

    delay(1000);
  }
}

void count(int top){
  for(int iterator=1;iterator <= top;iterator++){
    digitalWrite(13, HIGH);
    delay(350);
    digitalWrite(13, LOW);
    delay(200);
  }
}
