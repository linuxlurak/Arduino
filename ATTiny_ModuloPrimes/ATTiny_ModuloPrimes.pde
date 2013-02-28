
unsigned long f0=0;
unsigned long f1=1;
unsigned long fn;
int l1, l2, l3, l4, l5;

int fib(int f0, int f1)
{
  return(f0 + f1);
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<=4;i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  fn = f1 + f0;
  if(fn < f1){
    // Reset when unsigned long rolls over
    f0 = 0;
    f1 = 1;
  }else{
    f0 = f1;
    f1 = fn;
    if(fn % 2 == 0){
      digitalWrite(0,HIGH);
    }else{
      digitalWrite(0,LOW);
    }
    if(fn % 3 == 0){
      digitalWrite(1,HIGH);
    }else{
      digitalWrite(1,LOW);
    }
    if(fn % 5 == 0){
      digitalWrite(2,HIGH);
    }else{
      digitalWrite(2,LOW);
    }
    if(fn % 7 == 0){
      digitalWrite(3,HIGH);
    }else{
      digitalWrite(3,LOW);
    }
    if(fn % 11 == 0){
      digitalWrite(4,HIGH);
    }else{
      digitalWrite(4,LOW);
    }
  }
  delay(100);
}
