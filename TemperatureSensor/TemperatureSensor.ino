//TMP36 Pin Variables
int sensorPin = 1; //the analog pin the TMP36's Vout (sense) pin is connected to
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
  //to view the result open the serial monitor 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()                     // run over and over again
{
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(sensorPin);  

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; 

  // print out the voltage
  Serial.print(voltage); 
  Serial.print(" volts\t");

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((volatge - 500mV) times 100)
  Serial.print(temperatureC); 
  Serial.print(" degrees C\t");

  // now convert to Fahrenheight
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); 
  Serial.println(" degrees F");
  if(temperatureF > 50){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  if(temperatureF > 55){
    digitalWrite(3, HIGH);
  }else{
    digitalWrite(3, LOW);
  }
  if(temperatureF > 60){
    digitalWrite(4, HIGH);
  }else{
    digitalWrite(4, LOW);
  }
  if(temperatureF > 65){
    digitalWrite(9, HIGH);
  }else{
    digitalWrite(9, LOW);
  }
  if(temperatureF > 70){
    digitalWrite(11, HIGH);
  }else{
    digitalWrite(11, LOW);
  }

  delay(1000);                                     //waiting a second
}

