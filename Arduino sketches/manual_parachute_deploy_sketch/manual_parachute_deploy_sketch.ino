int ledPin = 13;
char parachuteManualDeployCode[] = "54321";
char serialString[5];
int index = 0;
void setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0 )
 { 
    if (checkParachuteCode())
    {
       digitalWrite(ledPin,13);
       Serial.println("Parachute manually deployed"); 
    }
  }
}
boolean checkParachuteCode()
{
    while(Serial.available())
    {
        serialString[index++] = Serial.read();
        if(serialString[0] != '5')
          index = 0;
        Serial.println(serialString[index-1]);
    }
    if ( index == 5 )
    {
      index = 0;
      return strcmp(serialString, parachuteManualDeployCode) == 0;
    }
    else
      return false;
}
