
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
      analogLevel[pin]--;
      if(analogLevel[pin] <0){
        analogLevel[pin]=0;
      }
    }
    else{
      analogLevel[pin]++;
      if(analogLevel[pin]>255){
        analogLevel[pin]=255;
      }
    }
    analogWrite(pin, analogLevel[pin]);
  }
  for(int pin = 2; pin <=4; pin++){
    if(digitalState[pin]==HIGH){
      //Check if pin has been on for a random number amount of time
      //from 300 to 600 milliseconds and if so, turn it off.
      if(millis() - onTime[pin] > (300 + random(300))){
        digitalWrite(pin, LOW);
      }
    }
    else{
      //If pin is not on, use 10% probability of turning it on
      if(random(99)<10){
        onTime[pin] = millis();
        digitalState[pin] = HIGH;
        digitalWrite(pin, HIGH);
      }
    }
  }
}


