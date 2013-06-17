// BigNumber test: calculate e
#include "BigNumber.h"
#include <SPI_VFD.h>

// initialize the library with the numbers of the interface pins
SPI_VFD vfd(2, 3, 4);

void setup ()
{
  Serial.begin (9600);
  vfd.begin(20, 2);
  Serial.println ();
  delay(3000);
  Serial.println("Starting up");

  BigNumber::begin (50);  // max around 160 on the Uno

  // some big numbers
  BigNumber n = 1, e = 1, one = 1, two = 2, minusone = -1, four = 4;

  int i = 1;
  BigNumber sum = 0, denominator = 1, sign = 1, previous = 0;  // previous result

  unsigned long start = millis ();
  do
  { 
    Serial.print("Loop ");
    previous = sum;
    sum = sum + sign * (one / denominator);
    denominator = denominator + two;
    sign = sign * minusone;
    Serial.print("iteration ");
    Serial.print(i);
    Serial.print("  Pi = ");
    Serial.println(four * sum);
    vfd.setCursor(0, 0);
    vfd.print("pi = ");
    vfd.print(four * sum);
    //delay(100);
    i++;
  }  
  while (previous != sum);
  unsigned long time = millis () - start;

  Serial.println (four * sum);
  Serial.print (time);
  Serial.println (" mS");
} // end of setup

void loop () { 
}


