/*
 A light that turns on when triggered and then slowly fades out.
 
 */


int ledPin = 3;    // LED connected to digital pin 3
int inputPin = 10;
int builtInPin = 13;
int builtInPinState = 0;

void setup()  {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(builtInPin, OUTPUT);
  digitalWrite(inputPin, HIGH); //Turn on pullup resistor
} 

void loop()  { 
  if(builtInPinState == 1){
    digitalWrite(builtInPin, HIGH);
    Serial.print(builtInPinState);
    Serial.println("   On");
  }else if(builtInPinState == 35){
    digitalWrite(builtInPin, LOW);
    Serial.print(builtInPinState);
    Serial.println("   Off");
  }else if(builtInPinState == 45){
    digitalWrite(builtInPin, HIGH);
    Serial.print(builtInPinState);
    Serial.println("   On");
  }else if(builtInPinState == 80){
    digitalWrite(builtInPin, LOW);
    Serial.print(builtInPinState);
    Serial.println("   Off");
  }else if(builtInPinState > 300){
    builtInPinState = 0;
    Serial.print(builtInPinState);
    Serial.println("   ResetCounter");
  }
  if(digitalRead(inputPin)==0){
      fadeOn();
    }
  builtInPinState++;
  delay(10);
}

void fadeOn (void){
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=1) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    delay(40);                            
  }
  fadeOut();
}

void fadeOut (void){
  int delaytime = 1000;
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=1) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    if(fadeValue < 10){
      delaytime += 1000;
    }    
    delay(delaytime);                            
  } 
}


