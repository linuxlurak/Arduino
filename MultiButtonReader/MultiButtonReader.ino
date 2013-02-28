/*

 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  for(int i=2;i<=7;i++){
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);
  }
}

void loop(){
  // read the state of the pushbutton value:
  for(int i=2;i<=7;i++){
    buttonState = digitalRead(buttonPin);
    Serial.print("Pin ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(buttonState);
    Serial.print(" ");
  }
  Serial.println("");
  delay(500);
}
