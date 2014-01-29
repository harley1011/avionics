//Global Variables and Constants

const int LED_PIN = 0;
const int MODE1_MODE2 = 500; //500 ft altitude detected, switch from mode 1 to mode 2
const int DROGUE_EMATCH_PIN = 1; //Pin connected to drogue parachute e-match
const int MAIN_EMATCH_PIN = 2; //Pin connected to main parachute e-match
const int ACCEL_THRESH = 3; // Acceleration upper threshold for apogee detection

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(DROGUE_EMATCH_PIN, OUTPUT);
  pinMode(MAIN_EMATCH_PIN, OUTPUT);
}

void loop()
{
 
 delay(500) // intial delay for all electronics
 
 //Read in pressure values
 //Average pressure calculations (to calculate mainChutePressure)
 
  do
  {
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
  }
  
  while(rocketAltitude<mode1_mode2) 
 
  if (vertAccel < ACCEL_THRESH) 
  {
  
    digitalWrite(DROGUE_EMATCH_PIN, HIGH);
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
    //Include extra statement in serial transmission to indicated when parachute was deployed
  
  }
  
  else
  {
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
  }

}
