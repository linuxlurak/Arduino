
int analogLevel[]= {
  128, 128};
int digitalState[]={
  LOW, LOW, LOW, LOW, HIGH};
unsigned long onTime[]={
  0, 0, 0, 0, 0,};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<=4;i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int pin = 0; pin <=1; pin++){
    if(random(99)<50){
      analogLevel[pin]-=5;
      if(analogLevel[pin] <0){
        analogLevel[pin]=0;
      }
    }
    else{
      analogLevel[pin]+=5;
      if(analogLevel[pin]>255){
        analogLevel[pin]=255;
      }
    }
    analogWrite(pin, analogLevel[pin]);
  }
  for(int pin = 2; pin <=4; pin++){
    if(digitalState[pin]==HIGH){
      //Check if pin has been on for a random number amount of time
      //from 500 to 800 milliseconds and if so, turn it off.
      if(millis() - onTime[pin] > (500 + random(300))){
        digitalState[pin] = LOW;
        digitalWrite(pin, LOW);
      }
    }
    else{
      //If pin is not on, use 1% probability of turning it on
      //but only if the last "On Time" was at least 3 seconds ago
      if(millis() - onTime[pin] > 3000){
      if(random(99)<1){
        onTime[pin] = millis();
        digitalState[pin] = HIGH;
        digitalWrite(pin, HIGH);
      }
      }
    }
  }
}



