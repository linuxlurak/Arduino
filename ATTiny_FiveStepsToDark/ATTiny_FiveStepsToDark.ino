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
//  pinMode(10, OUTPUT);
//  pinMode(11, OUTPUT);
  analogWrite(0,255);
  analogWrite(1,255);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  delay(60000);
  digitalWrite(4,LOW);
  delay(60000);
  digitalWrite(3,LOW);
  delay(60000);
  digitalWrite(2,LOW);
  for(int i=255;i>=0;i--){
    analogWrite(1,i);
    delay(500);
  }  
  for(int i=255;i>=0;i--){
    analogWrite(0,i);
    delay(500);
  }
  sleepNow();
}

void loop() {
  // put your main code here, to run repeatedly: 
  for(int i=0;i<=4;i++){
    digitalWrite(i,HIGH);
    delay(1000);
    digitalWrite(i,LOW);
  }
}
