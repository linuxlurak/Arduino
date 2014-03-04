/*
  Fireflies
  Blink LEDs at random intervals and for random durationo 
*/
const int numberOfFireflies = 8;
const int maxInterval = 60000; // Longest time between flashes of a specific led
int ledState[numberOfFireflies];
unsigned long ledStartTime[numberOfFireflies]; // start of flickering on interval
unsigned long ledTargetDuration[numberOfFireflies]; // duration of on+fadeout

void setup() {                
  // initialize the digital pin as an output.
  // start at pin 3
  for(int led=3;led< 3+numberOfFireflies;led++){
    pinMode(led, OUTPUT);
    ledState[led] = LOW;
    ledStartTime[led] = millis();
  }    
}

// the loop routine runs over and over again forever:
void loop() {
  for(int led=3;led< 3+numberOfFireflies;led++){
    if(ledState[led] == LOW){
      if(millis() - ledStartTime[numberOfFireflies] < ledTargetDuration[numberOfFireflies]){
        digitalWrite(led, HIGH);
        ledState[led] = HIGH;
      }else{
        ledStartTime[numberOfFireflies] = millis() + random(maxInterval);
      }
    }else{
      if(millis() - ledStartTime[numberOfFireflies] > ledTargetDuration[numberOfFireflies]){
        digitalWrite(led, LOW);
        ledState[led] = LOW;
      }else{
        unsigned long toggleChance = random(millis() - ledStartTime[numberOfFireflies]);
        // toggleChance is a random number between zero and maxInterval
        // higher numbers are more likely to occur the longer the led has been on
      }
    }
  }
}

void bogoPWM(int percentage){
  // Fake a sort of PWM by turning off after percentage on time
  static unsigned long ledTurnOnTime[numberOfFireflies];
}
