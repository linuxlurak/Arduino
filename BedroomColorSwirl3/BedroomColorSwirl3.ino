// Photodiode logic to be implemented
// If photoDiode > 35, ambient = BRIGHT
// If ambient == BRIGHT and photoDiode < 15, ambient = DIM and mode = 1


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
    //    red();
    quickFade();
    break;
    case(2):
    //    green();
    slowFade();
    break;
    case(3):
    //    blue();
    mostlyRed();
    break;
    case(4):
    //    redblue();
    fadeOut();
    break;
  }
}

void quickFade(){
  static unsigned long lastChange = millis();
  unsigned long interval = 100;
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(mode != oldmode) { // Just entered this mode
    for(int i=0;i<4;i++){
      red();
      blue();
    }
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
    r1 = converge(r1, r2);
    analogWrite(REDPIN, r1);

    g1 = converge(g1, g2);
    analogWrite(GREENPIN, g1);

    b1 = converge(b1, b2);
    analogWrite(BLUEPIN, b1);
  }
}

void slowFade(){
  static unsigned long lastChange = millis();
  unsigned long interval = 2000;
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(mode != oldmode) { // Just entered this mode
    for(int i=0;i<3;i++){
      green();
      blue();
    }
  }

  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2 && g1 == g2 && b1 == b2){
        r2 = random(0,255);
        g2 = random(0,255);
        b2 = random(0,255);
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
  unsigned long interval = 3000;
  if(lastChange > millis()){ // millis() counter wrapped
    lastChange = 0; // I'm still not sure how to handle this accurately
  }
  if(mode != oldmode) { // Just entered this mode
    for(int i=0;i<3;i++){
      red();
      green();
    }
    g1 = random(10,50);
    b1 = random(10,50);
  }

  if(millis() - lastChange > interval){
    lastChange = millis();
    if(r1 == r2){
      r2 = random(100,255);
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
    int blinker = random(0,100);
    if(blinker > 95){
      analogWrite(BLUEPIN, 0);
    }
    else if(blinker > 90){
      analogWrite(GREENPIN, 0);
    }
  }
}

void fadeOut(){
  static unsigned long lastChange = millis();
  static unsigned long interval = 6000;
  if(mode != oldmode) { // Just entered this mode
      r1 = random(100,255);
      g1 = random(50,200);
      b1 = random(50,200);
    interval = (60000 * 10) / r1; // 10 minutes divided by steps to zero
    for(int i=0;i<3;i++){
      off();
      red();
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

float magnitude2(int r, int g, int b){
  return (r^2 + g^2 + b^2);
}

void red(void){
  r2 = 255;
  g2 = 0;
  b2 = 0;
  for(int i = 0;i<255;i++){
    r1 = converge(r1, r2);
    g1 = converge(g1, g2);
    b1 = converge(b1, b2);
    analogWrite(REDPIN, r1);
    analogWrite(GREENPIN, g1);
    analogWrite(BLUEPIN, b1);
    delay(1);
  }
}

void green(void){
  r2 = 0;
  g2 = 255;
  b2 = 0;
  for(int i = 0;i<255;i++){
    r1 = converge(r1, r2);
    g1 = converge(g1, g2);
    b1 = converge(b1, b2);
    analogWrite(REDPIN, r1);
    analogWrite(GREENPIN, g1);
    analogWrite(BLUEPIN, b1);
    delay(1);
  }
}

void blue(void){
  r2 = 0;
  g2 = 0;
  b2 = 255;
  for(int i = 0;i<255;i++){
    r1 = converge(r1, r2);
    g1 = converge(g1, g2);
    b1 = converge(b1, b2);
    analogWrite(REDPIN, r1);
    analogWrite(GREENPIN, g1);
    analogWrite(BLUEPIN, b1);
    delay(1);
  }
}

void redblue(void){
  r2 = 255;
  g2 = 0;
  b2 = 255;
  for(int i = 0;i<255;i++){
    r1 = converge(r1, r2);
    g1 = converge(g1, g2);
    b1 = converge(b1, b2);
    analogWrite(REDPIN, r1);
    analogWrite(GREENPIN, g1);
    analogWrite(BLUEPIN, b1);
    delay(1);
  }
}

void off(void){
  r2 = 0;
  g2 = 0;
  b2 = 0;
  for(int i = 0;i<255;i++){
    r1 = converge(r1, r2);
    g1 = converge(g1, g2);
    b1 = converge(b1, b2);
    analogWrite(REDPIN, r1);
    analogWrite(GREENPIN, g1);
    analogWrite(BLUEPIN, b1);
    delay(1);
  }
}

