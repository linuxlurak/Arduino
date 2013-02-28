
int led_order[] = { 
  8, 7, 6, 5, 2, 3, 4};


void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<7;i++){
    pinMode(led_order[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  for(int j=1;j<80;j++){
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],HIGH);
      delay(j);
      digitalWrite(led_order[i],LOW);
      delay(j);
    }
    Serial.println(j);
  }
  for(int k=1;k<8;k++){
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],HIGH);
    }
    delay(120);
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],LOW);
    }
    delay(75);
  }
  for(int j=80;j>0;j--){
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],HIGH);
      delay(j);
      digitalWrite(led_order[i],LOW);
      delay(j);
    }
    Serial.println(j);
  }
  for(int k=1;k<8;k++){
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],HIGH);
    }
    delay(60);
    for(int i=0;i<7;i++){
      digitalWrite(led_order[i],LOW);
    }
    delay(165);
  }
}


