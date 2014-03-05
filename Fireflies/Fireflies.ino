/*
  Fireflies
  Blink LEDs at random intervals and for random durationo 
*/
const int numberOfFireflies = 8;
const int firstLED = 3;
const int maxInterval = 60000; // Longest time between flashes of a specific led
const int maxDuration = 10000; // Longest time for a firefly to stay lit
int ledState[numberOfFireflies];
unsigned long ledStartTime[numberOfFireflies]; // start of flickering on interval
unsigned long ledTargetDuration[numberOfFireflies]; // duration of on+fadeout

void setup() {                
  // initialize the digital pin as an output.
  for(int led=0;led < numberOfFireflies;led++){
    pinMode(led + firstLED, OUTPUT);
    ledState[led] = LOW;
    ledStartTime[led] = millis();
  }    
}

// the loop routine runs over and over again forever:
void loop() {
  for(int led=0;led< numberOfFireflies;led++){
    if(ledState[led] == LOW){
      if(millis() < ledStartTime[led]){
        // Do nothing
      }
      else if(millis() - ledStartTime[led] < ledTargetDuration[led]){
        digitalWrite(led + firstLED, HIGH);
        ledState[led] = HIGH;
      }else{
        ledStartTime[led] = millis() + random(maxInterval);
        ledTargetDuration[led] = random(250, maxDuration);
      }
    }else{
      if(millis() - ledStartTime[led] > ledTargetDuration[led]){
        digitalWrite(led + firstLED, LOW);
        ledState[led] = LOW;
      }else{
        unsigned long toggleChance = random(millis() - ledStartTime[led]);
        // toggleChance is a random number between zero and maxInterval
        // higher numbers are more likely to occur the longer the led has been on
      }
    }
  }
}

boolean bogoPWM(int led, int percentage){
  // Fake a sort of PWM by turning off after percentage on time
  static unsigned long ledTurnOnTime[numberOfFireflies];
}
