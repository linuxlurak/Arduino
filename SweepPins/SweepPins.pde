/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

void setup() {
//  Serial.begin(9600);
  for(int i=2;i<=13;i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int sensorValue = analogRead(A0);
  if(sensorValue < 100){
    digitalWrite(2, HIGH);
  }
  if(101 < sensorValue < 200){
    digitalWrite(3, HIGH);
  }
  if(201 < sensorValue < 300){
    digitalWrite(4, HIGH);
  }
  if(301 < sensorValue < 400){
    digitalWrite(5, HIGH);
  }
  if(401 < sensorValue < 500){
    digitalWrite(6, HIGH);
  }
  if(501 < sensorValue < 600){
    digitalWrite(7, HIGH);
  }
  if(601 < sensorValue < 700){
    digitalWrite(8, HIGH);
  }
  if(701 < sensorValue < 800){
    digitalWrite(9, HIGH);
  }
  if(801 < sensorValue < 900){
    digitalWrite(10, HIGH);
  }
  if(901 < sensorValue < 1000){
    digitalWrite(11, HIGH);
  }
  if(1001 < sensorValue){
    digitalWrite(12, HIGH);
  }
  for(int i=2;i<=13;i++){
    digitalWrite(i, LOW);
  }
}
