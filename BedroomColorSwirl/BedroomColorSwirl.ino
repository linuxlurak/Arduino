// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 10
#define GREENPIN 9
#define BLUEPIN 11
 
#define FADESPEED 100     // make this higher to slow down
 
void setup() {
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(2, INPUT);
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  delay(1000);
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 255);
  analogWrite(BLUEPIN, 255);
  delay(1000);
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  delay(1000);
  for (int l = 0; l <= 255; l++){
    analogWrite(REDPIN, l);
    analogWrite(GREENPIN, l);
    analogWrite(BLUEPIN, l);
    delay(FADESPEED);
  }
  int l, r, g, b;

  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  }
  Serial.println("1");
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("2");
  // fade from blue to violet
  for (r = 0; r <= 255; r++) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("3");
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("4");
  // fade from red to yellow
  for (g = 0; g <= 255; g++) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("5");
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("6");
  // fade from green to teal
  for (b = 0; b <= 200; b++) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("7");
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("8");
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("9");
  for (r = 0; r <= 255; r++) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("10");
  for (g = 0; g <= 150; g++) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("11");
  for (b = 0; b <= 255; b++) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
  Serial.println("12");
  for (b = 255; b >=0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED * 4);
  } 
  Serial.println("13");
  for (g = 255; g >=0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED * 8);
  } 
  Serial.println("14");
  for (r = 255; r >= 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED * 13);
  } 
  Serial.println("15");


  for (int l = 0; l <= 255; l++){
    analogWrite(REDPIN, l/2);
    analogWrite(BLUEPIN, l);
    delay(FADESPEED);
  }
  Serial.println("16");
 
  for (int l = 255; l >= 0; l--){
    analogWrite(REDPIN, l/2);
    analogWrite(BLUEPIN, l);
    delay(FADESPEED);
  }
  Serial.println("17");

  for (int l = 0; l <= 255; l++){
    analogWrite(GREENPIN, l);
    analogWrite(BLUEPIN, l/2);
    delay(FADESPEED);
  }
  Serial.println("18");
  for (int l = 255; l >= 0; l--){
    analogWrite(GREENPIN, l);
    analogWrite(BLUEPIN, l/2);
    delay(FADESPEED);
  }
  Serial.println("19");


  for (int l = 0; l <= 255; l++){
    analogWrite(REDPIN, l);
    analogWrite(GREENPIN, l/2);
    delay(FADESPEED);
  }
  Serial.println("20");
  for (int l = 255; l >= 0; l--){
    analogWrite(REDPIN, l);
    analogWrite(GREENPIN, l/2);
    delay(FADESPEED);
  }
  Serial.println("21");


  for (int l = 0; l <= 255; l++){
    analogWrite(REDPIN, l);
    analogWrite(GREENPIN, l);
    analogWrite(BLUEPIN, l);
    delay(FADESPEED);
  }
  Serial.println("22");



  for (b = 255; b >=0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED * 10);
  } 
  Serial.println("23");
  for (g = 255; g >=0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED * 20);
  } 
  Serial.println("24");
  for (r = 255; r >= 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED * 30);
  } 
  Serial.println("25");
}
 
 
void loop() {

}

void waitForInput(){
  int flag = 0;
  /*
  while(!flag){
    flag = digitalRead(2);
  }
  */
}
