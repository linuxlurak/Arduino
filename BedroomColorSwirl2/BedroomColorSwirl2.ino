// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9
 
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
 
  redDown();
  Serial.println("1");
  greenDown();
  Serial.println("2");

  redUp();
  Serial.println("3");
  
  blueDown();
  Serial.println("4");
  
  greenUp();
  Serial.println("5");
  
  redDown();
  Serial.println("6");
  
  blueUp();
  Serial.println("7");
  
  greenDown();
  Serial.println("8");
  
  blueDown();
  Serial.println("9");
  
  redUp();
  Serial.println("10");
  
  greenUp();
  Serial.println("11");
  
  blueUp();
  Serial.println("12");
  
  blueDown();
  Serial.println("13");
  
  greenDown();
  Serial.println("14");
  
  redDown();
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

void redUp(){
    for (r = 0; r <= 255; r++) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  } 
}
void redDown(){
    for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    waitForInput();
    delay(FADESPEED);
  }
}

void greenUp(){
    for (g = 0; g <= 255; g++) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
}
void greenDown(){
    for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    waitForInput();
    delay(FADESPEED);
  } 
}

void blueUp(){
    for (b = 0; b <= 200; b++) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
}
void blueDown(){
    for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    waitForInput();
    delay(FADESPEED);
  } 
}
