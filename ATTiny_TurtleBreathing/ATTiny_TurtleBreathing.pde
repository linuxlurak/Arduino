#include <avr/sleep.h>
#


void sleepNow()         // here we put the arduino to sleep
#
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<=4;i++){
    pinMode(i, OUTPUT);
  }
  for(int j=255;j>=0;j--){
    for(int i = 0; i<=j; i++){
      analogWrite(0, i);
      analogWrite(1, j-i);
      delay(45);
    }
    for(int i = j; i>=0; i--){
      analogWrite(0, i);
      analogWrite(1, j-i);
      delay(45);
    }
  }
  sleepNow();
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(0,255);
  analogWrite(1,0);
  delay(1000);
  analogWrite(0,0);
  analogWrite(1,255);
  delay(1000);
}

