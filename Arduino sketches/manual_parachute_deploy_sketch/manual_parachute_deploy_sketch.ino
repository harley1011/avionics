int ledPin = 13;
char parachuteManualDeployCode[] = "123456789";
void setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0 ) 
  {
  /*if (Serial.read() == 'D'){
  //ring the bell briefly
  digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }*/
    if (checkParachuteCode())
    {
      digitalWrite(ledPin,13);
      Serial.println("Parachute manually deployed"); 
    }
  }
}
boolean checkParachuteCode()
{
  char serialString[10];
  int index = 0;
    while(Serial.available())
    {
        serialString[index++] = Serial.read();
    }
    return strcmp(serialString, parachuteManualDeployCode) == 0;
}
