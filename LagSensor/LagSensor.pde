/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

int lag;
int lagCount = 10000; // what we count to before changing output
int lagChange = 0; //Boolean, are we counting lag time
int lastSensor = 0;


void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  if(abs(sensorValue - lastSensor) > 5){
    lastSensor = sensorValue;
    lagChange = 1;
  }
  if(lagChange == 1){
    if(lag > lagCount){
      analogWrite(9, lastSensor / 4);
      lagChange = 0;
      lag = 0;
    }else{
      lag++;
    }
  }
  Serial.print(sensorValue, DEC);
  Serial.print("\t");
  Serial.print(lastSensor, DEC);
  Serial.println(sensorValue / 4, DEC);
  }
