
int redPin = 9;
int redLevel = 192;
int greenPin = 10;
int greenLevel = 192;
int bluePin = 11;
int blueLevel = 192;
unsigned long stepLength = 99;
unsigned long lastStepEnd = millis();

void setup(){
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    Serial.begin(9600);
}

void loop(){
  if(millis() < lastStepEnd){
    /* Clock has rolled over */
    unsigned long fragmentBeforeRollover = 4294967295 - lastStepEnd;
    if(millis() + fragmentBeforeRollover > stepLength){
      stepAction();
    }
  }else if(millis() - lastStepEnd > stepLength){
    stepAction();
    lastStepEnd = millis();
  }
}

void stepAction(){
  Serial.print("millis:\t");
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(redLevel);
  Serial.print("\t");
  Serial.print(greenLevel);
  Serial.print("\t");
  Serial.print(blueLevel);  
  Serial.println("");
  if(random(1000) < 501){
    redLevel = redLevel - 1;
    if(redLevel < 0){
      redLevel = 0;
    }
  }else{
    redLevel = redLevel + 1;
    if(redLevel > 255){
      redLevel = 255;
    }
  }
  if(random(1000) < 501){
    blueLevel = blueLevel - 1;
    if(blueLevel < 0){
      blueLevel = 0;
    }
  }else{
    blueLevel = blueLevel + 1;
    if(blueLevel > 255){
      blueLevel = 255;
    }
  }
  if(random(1000) < 501){
    greenLevel = greenLevel - 1;
    if(greenLevel < 0){
      greenLevel = 0;
    }
  }else{
    greenLevel = greenLevel + 1;
    if(greenLevel > 255){
      greenLevel = 255;
    }
  }
  analogWrite(redPin, redLevel);
  analogWrite(bluePin, blueLevel);
  analogWrite(greenPin, greenLevel);
}
