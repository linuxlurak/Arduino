/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
 Center pin of the potentiometer goes to the analog pin.
 side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int invertedOutPin = 11; //Analog out inverted with sensor

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int invertedOutputValue=0;
int counter=1; // Count readings for an average
int totalSensorValue=0; // Total multiple readings for an average

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  if(counter <=10){
    totalSensorValue += analogRead(analogInPin);
    counter++;
  }
  else{
    counter=1;
    sensorValue = totalSensorValue / 10;
    totalSensorValue = 0;    
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 8, 32, 0, 255);
    invertedOutputValue = map(sensorValue, 32, 8, 255, 0);  
    // change the analog out value:
    analogWrite(analogOutPin, outputValue);           
    analogWrite(invertedOutPin, invertedOutputValue);

    // print the results to the serial monitor:
    Serial.print("sensor = " );                       
    Serial.print(sensorValue);      
    Serial.print("\t output = ");      
    Serial.print(outputValue);
    Serial.print("\t inverted output = ");
    Serial.println(invertedOutputValue);  
  }
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(20);                     
}

