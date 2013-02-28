
int count;
int timer=30;

void setup() {
  Serial.begin(9600);
  for(count=2;count<9;count++){
  pinMode(count, OUTPUT);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH); //Turn on pullup resistor
  pinMode(11, INPUT);
  digitalWrite(11, HIGH); //Turn on pullup resistor
  pinMode(12, INPUT);
  digitalWrite(11, HIGH); //Turn on pullup resistor
}

}

void loop() {
  //Serial.print("Pin 10 Button: ");
  //Serial.println(digitalRead(10));
  //Serial.print("Pin 11 Button: ");
  //Serial.println(digitalRead(11));
  //Serial.print("Pin 12 Button: ");
  //Serial.println(digitalRead(12));


//  Serial.println("Countup");
  for(count=3;count<9;count++){
  //  Serial.println(count);
    digitalWrite(count, HIGH);
    mydelay(timer);
    digitalWrite(count+1, HIGH);
    mydelay(timer);
    digitalWrite(count, LOW);
    mydelay(timer*2);
  }
  
  //Serial.println("Countdown");
  for(count=7;count>1;count--){
    //Serial.println(count);
    digitalWrite(count, HIGH);
    mydelay(timer);
    digitalWrite(count-1, HIGH);
    mydelay(timer);
    digitalWrite(count, LOW);
    mydelay(timer*2);
  }
}

void mydelay(int limit){
  
  static unsigned long waitlimit = 5000;
  unsigned long loopcount = 0;
  //delay(limit);
  Serial.print("waitlimit: ");
  Serial.print(waitlimit);
  Serial.print("\t loopcount: ");
  Serial.println(loopcount);

  
  while(loopcount < waitlimit){
    if(digitalRead(10)==0){
      waitlimit += 1;
    }
    if(digitalRead(12)==0){
      waitlimit -= 1;
    }
    if(waitlimit > 100000){
      waitlimit = 100000;
    }
    if(waitlimit < 2){
      waitlimit = 2;
    }
    loopcount++;
  }
}
