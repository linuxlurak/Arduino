#define REDPIN 10
#define GREENPIN 9
#define BLUEPIN 11

#define FADESPEED 100     // make this higher to slow down

int r1 = random(0,255);
int g1 = random(0,255);
int b1 = random(0,255);
int r2 = random(0,255);
int g2 = random(0,255);
int b2 = random(0,255);
int mode;
int oldmode;
unsigned long modeChangeTime;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(13, OUTPUT);
  for(int i=4;i<=6;i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(8, INPUT_PULLUP);
}

void loop(){
  oldmode = mode;
  mode = pollButtons();
  if(mode != oldmode){
    modeChangeTime = millis();
  }
  switch(mode){
    case(1):
    brightSlowFade();
    break;
    case(2):
    dimSlowFade();
    break;
    case(3):
    mostlyRed();
    break;
    case(4):
    fadeOut();
    break;
  }
}

void brightSlowFade(){
  static unsigned long lastChange = millis();
  unsigned long interval = 700;
  if(millis() - lastChange < 0){ // millis() counter wrapped
    lastChange = interval - (2 ^ 32 - lastChange);
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
      r2 = random(0,255);
      g2 = random(0,255);
      b2 = random(0,255);
      int tweak = random(0,100);
      if(tweak > 75){
        g2 = g2 / 2;
      }
      else if(tweak > 50){
        b2 = b2 / 2;
      }
      else if(tweak > 25){
        g2 = g2 / 2;
        b2 = b2 / 2;
      }
    }
    if(r1 > r2){
      r1--;
    }
    else if(r1 < r2){
      r1++;
    }
    analogWrite(REDPIN, r1);
    if(g1 > g2){
      g1--;
    }
    else if(g1 < g2){
      g1++;
    }
    analogWrite(GREENPIN, g1);
    if(b1 > b2){
      b1--;
    }
    else if(b1 < b2){
      b1++;
    }
    analogWrite(BLUEPIN, b1);
  }
}

void dimSlowFade(){
  static unsigned long lastChange = millis();
  unsigned long interval = 2000;
  if(millis() - lastChange < 0){ // millis() counter wrapped
    lastChange = interval - (2 ^ 32 - lastChange);
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
      r2 = random(0,100);
      g2 = random(0,20);
      b2 = random(0,20);
    }
    if(r1 > r2){
      r1--;
    }
    else if(r1 < r2){
      r1++;
    }
    analogWrite(REDPIN, r1);
    if(g1 > g2){
      g1--;
    }
    else if(g1 < g2){
      g1++;
    }
    analogWrite(GREENPIN, g1);
    if(b1 > b2){
      b1--;
    }
    else if(b1 < b2){
      b1++;
    }
    analogWrite(BLUEPIN, b1);
  }
}

void mostlyRed(){
  static unsigned long lastChange = millis();
  unsigned long interval = 10000;
  if(millis() - lastChange < 0){ // millis() counter wrapped
    lastChange = interval - (2 ^ 32 - lastChange);
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
      r2 = random(0,100);
    }
    if(r1 > r2){
      r1--;
    }
    else if(r1 < r2){
      r1++;
    }
    analogWrite(REDPIN, r1);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 0);
  }
  //if(g1 == 0){
  //g1 = 1;
  //}
  //else{
  g1 = 0;
  //}
  //analogWrite(GREENPIN, g1);
  //if(b1 = 0){
  //b1 = 1;
  //}
  //else{
  b1 = 0;
  //}
  //analogWrite(BLUEPIN, b1);
}

void fadeOut(){
  static unsigned long lastChange = millis();
  static unsigned long interval = 20000;
  if(mode != oldmode) { // Just entered this mode
    int intervals[] = {1400, 1400, 700, 470, 350, 280, 230, 200, 175, 155, 140, 126, 115, 107, 99, 92, 87, 82, 77, 73, 69, 66, 63, 60, 58, 56, 54, 52, 50, 48, 46, 45, 44, 42, 41, 40, 39, 38, 37, 36, 35, 35, 34, 33, 32, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23, 23, 23, 22, 22, 22, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
    interval = intervals[r1] * 1000;
  }
  if(millis() - lastChange < 0){ // millis() counter wrapped
    lastChange = interval - (2 ^ 32 - lastChange);
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 > 0){
      r1--;
      analogWrite(REDPIN, r1);
    }
    if(g1 > 0){
      g1 -= 4;
      analogWrite(GREENPIN, g1);
    }
    if(b1 > 0){
      b1 -= 5;
      analogWrite(BLUEPIN, b1);
    }
  }
}

int pollButtons(){
  static int retval = 1;
  //  for(int pin=4;pin <= 6;pin++){
  //  if(digitalRead(pin)==LOW){
  //  retval = 2^(pin - 4);
  //digitalWrite(13, HIGH);
  // }
  // }
  if(digitalRead(4)==LOW){ //Button 3
    retval = 3;
  }
  if(digitalRead(5)==LOW){ // Button 4
    retval = 4;
  }
  if(digitalRead(6)==LOW){ //Button 1
    retval = 1;
  }
  if(digitalRead(8)==LOW){ // Button 2
    retval = 2;
  }
  return(retval);
}

void dither(int c1, int c2, char c, long wait){
  int pin;
  long start = millis();
  if(c == 'r'){
    pin = REDPIN;
  }
  else if(c == 'g'){
    pin = GREENPIN;
  }
  else if(c == 'b'){
    pin = BLUEPIN;
  }
  while((millis() - start) < wait){
    analogWrite(pin, c1);
    analogWrite(pin, c2);
  }
}






