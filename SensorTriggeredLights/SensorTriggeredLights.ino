
// ENUM doesn't seem to work so using integers to track Finite
// State Machine state.
int state=0; //PWM1OFF

// A switch statement within the main loop contains a case
// for each state in the FSM. Within the case we check for
// sensor readings that would trigger a state change. In
// the event of a change in sensor readings a subroutine
// will be called to execute a state change.

// Each state change subroutine will continue to check for
// sensor changes while executing the state change. If a
// sensor changes state the subroutine will immediately
// return so that the main loop's switch statement can
// determine the appropriate state transition.

// In general a state change subroutine will start by setting
// a state that is a transition state (e.g. PWM1FADINGUP) and
// finish by setting its destination state (e.g. PWM1OFF) before
// returning to the main loop.

int pwm1 = 3;
int lightSensor = 10; //LOW=Darkness
int irSensor = 12; //LOW=IR Detected
int currentPWM1=0; // Keep track of current output setting
unsigned long pwm1OnTime; // Time when PWM1 reached full on state
unsigned long lastTriggerTime; // Last time when a trigger was detected
// A trigger is generally IR activity. Maybe light change too.
unsigned long onDuration = 5 * 60 * 1000; // Desired duration of
// light after either on time or last "trigger" detection.
int prevLightState=LOW; //record whether it was light or dark last read

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lightSensor, INPUT);
  digitalWrite(lightSensor, HIGH);
  pinMode(irSensor, INPUT);
  digitalWrite(irSensor, HIGH);
  pinMode(pwm1, OUTPUT);
  analogWrite(pwm1, 0);
  delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly: 
  switch(state)
  {
    case 0:
//    case PWM1OFF:
      Serial.println("PWM1 Off");
      if(prevLightState == HIGH && digitalRead(lightSensor) == LOW){
        slowFadeUp();
      }
      break;
    case 1:
//    case PWM1ON:
      Serial.println("PWM1 On");
      if(digitalRead(irSensor) == LOW){
        lastTriggerTime = millis();
      }
      if(digitalRead(lightSensor) == HIGH){
        quickFadeDown();
      }
      if((millis() - lastTriggerTime)>onDuration){
        slowFadeDown();
      }
      break;
    case 2:
//    case PWM1FADINGUP:
      Serial.println("PWM1 Fading Up");
      break;
    case 3:
//    case PWM1FADINGDOWN:
      Serial.println("PWM1 Fading Down");
      break;
  }
  delay(10000);
  state++;
}

void slowFadeUp () {
  for(int x=currentPWM1;x<=255;x++){
    analogWrite(pwm1, x);
    currentPWM1 = x;
    for(int y=0;y<=100;y++){
      if(digitalRead(lightSensor)==HIGH){
        return;//Abort the fade up if bright light is detected
      }
      delay(10);
    }
  }
}

void slowFadeDown () {
  for(int x=currentPWM1;x>0;x--){
    analogWrite(pwm1, x);
    currentPWM1 = x;
    for(int y=0;y<=100;y++){
      if(digitalRead(irSensor)==LOW){
        return;//Abort the fade down if motion is detected
      }
      delay(10);
    }
  }
}

void quickFadeUp () {
  
}

void quickFadeDown () {
  
}


