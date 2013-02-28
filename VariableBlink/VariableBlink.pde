/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

int lag;
int lagCount = 100; // what we count to before changing output
int lastSensor = 0;


void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  if(abs(sensorValue - lastSensor) > 5){
    lastSensor = sensorValue;
    lag = 0;
  }else{
    lag++;
    if(lag > lagCount){
      analogWrite(9, lastSensor / 4);
      lag = 0;
    }
  }

  Serial.println(lag, DEC);
//  Serial.print(sensorValue, DEC);
//  Serial.print("\t");
//  Serial.print(lastSensor, DEC);
//  Serial.println(sensorValue / 4, DEC);
}
