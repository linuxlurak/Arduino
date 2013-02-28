
int counter = 1;
long outerloop = 1;
int levels[] = {
  20, 40, 60, 80, 100};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<=4;i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  if(counter == 1){
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  for(int led = 0; led<=4; led++){
    if(counter == levels[led]){
      digitalWrite(led, LOW);
    }
  }
  if(outerloop % 1000 == 0){
    levels[0]++;
    levels[1]++;
    levels[2]++;
    levels[3]++;
    levels[4]++;
    for(int index = 0; index <= 4; index++){
      if(levels[index] > 100){
        levels[index] = 1;
      }
    }
  }
  counter++;
  if(counter == 100){
    counter = 1;
  }
  outerloop++;
    if(outerloop == 100000){
    outerloop = 1;
  }
}



