// BigNumber test: calculate e
#include "BigNumber.h"

void setup ()
{
  Serial.begin (9600);
  Serial.println ();
  delay(3000);
  Serial.println("Starting up");

  BigNumber::begin (50);  // max around 160 on the Uno

  // some big numbers
  BigNumber n = 1, e = 1, one = 1;

  int i = 1;
  BigNumber E;  // previous result

  unsigned long start = millis ();
  do
  { 
    Serial.print("Loop ");
    E = e;
    n *= i++;  // n is i factorial
    e += one / n;
    Serial.print("iteration");
    Serial.print(i);
    Serial.print("  e = ");
    Serial.println(e);
    delay(100);
  }  while (e != E);
  unsigned long time = millis () - start;

  Serial.println (e);
  Serial.print (time);
  Serial.println (" mS");
} // end of setup

void loop () { }

