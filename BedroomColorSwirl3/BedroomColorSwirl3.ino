#define REDPIN 10
#define GREENPIN 11
#define BLUEPIN 9

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
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
      do{
        r2 = random(0,255);
        g2 = random(0,255);
        b2 = random(0,255);
      }
      while(magnitude(r2, g2, b2) < 216);
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
    r1 = converge(r1, r2);
    analogWrite(REDPIN, r1);

    g1 = converge(g1, g2);
    analogWrite(GREENPIN, g1);

    b1 = converge(b1, b2);
    analogWrite(BLUEPIN, b1);
  }
}

void dimSlowFade(){
  static unsigned long lastChange = millis();
  unsigned long interval = 2000;
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
      do{
        r2 = random(0,255);
        g2 = random(0,255);
        b2 = random(0,255);
      }
      while(magnitude(r2, g2, b2) > 50);    
    }
    r1 = converge(r1, r2);
    analogWrite(REDPIN, r1);

    g1 = converge(g1, g2);
    analogWrite(GREENPIN, g1);

    b1 = converge(b1, b2);
    analogWrite(BLUEPIN, b1);
  }
}

void mostlyRed(){
  static unsigned long lastChange = millis();
  unsigned long interval = 5000;
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2){
      r2 = random(0,100);
    }
    r1 = converge(r1, r2);
    analogWrite(REDPIN, r1);

    if(g1>1){
      g1--;
      analogWrite(GREENPIN, g1);
    }
    else if(b1>1){
      b1--;
      analogWrite(BLUEPIN, b1);
    }
  }
}

void fadeOut(){
  static unsigned long lastChange = millis();
  static unsigned long interval = 6000;
  if(mode != oldmode) { // Just entered this mode
    do{
      r1 = random(0,255);
      g1 = random(0,255);
      b1 = random(0,255);
    }
    while(magnitude(r1, g1, b1) > 216);
    if(r1 < 100){
      r1 += 100;
    }
  }
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 > 0){
      r1--;
      analogWrite(REDPIN, r1);
    }
    if(g1 >= 4){
      g1 -= 4;
    }
    else if(g1 > 0){
      g1--;
    }
    analogWrite(GREENPIN, g1);
    if(b1 >= 5){
      b1 -= 5;
    }
    else if(b1 > 0){
      b1--;
    }
    analogWrite(BLUEPIN, b1);

  }
}

int pollButtons(){
  static int retval = 1;
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

int converge(int c1, int c2){
  if(c1 > c2){
    c1--;
    return c1;
  }
  else if(c1 < c2){
    c1++;
    return c1;
  }
  return c1;
}

float magnitude(int r, int g, int b){
  return sqrt(r^2 + g^2 + b^2);
}




