/*
  Measure a photodiode on analog pin 0. Light up 0-5 LEDs based on input level.
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(11, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  if(sensorValue > 10){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }  
  if(sensorValue > 15){
    digitalWrite(3, HIGH);
  }else{
    digitalWrite(3, LOW);
  }  
  if(sensorValue > 20){
    digitalWrite(4, HIGH);
  }else{
    digitalWrite(4, LOW);
  }  
  if(sensorValue > 25){
    digitalWrite(9, HIGH);
  }else{
    digitalWrite(9, LOW);
  }  
  if(sensorValue > 27){
    digitalWrite(11, HIGH);
  }else{
    digitalWrite(11, LOW);
  }  
  delay(20);                  
}
