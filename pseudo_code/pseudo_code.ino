//Global variables and constants

const int LED_PIN = 0;
const int LAUNCH_THRESH = 300; //500 ft altitude detected, switch from mode 1 to mode 2
const int DROGUE_EMATCH_PIN = 1; //Pin connected to drogue parachute e-match
const int MAIN_EMATCH_PIN = 2; //Pin connected to main parachute e-match
const int APOGEE_ACCEL_THRESH = 3; // Acceleration upper threshold for apogee detection
const int MAIN_ALT_THRESH = 1800; //Altitude lower threshold for main chute deployment (1800 ft.)


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
 
 
 //Rocket pre-launch algorithm
  do
  {
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
  }
  while(rocketAltitude<LAUNCH_THRESH) 
 
 
 
  //Drogue parachute deployment algorithm 
  //Read and transmit data from all sensors while vertAccel greater than APOGEE_ACCEL_THRESH
  //Send current HIGH to DROGUE parachute e-match when vertAccel less than or equal to APOGEE_ACCEL_THRESH
  do
  {
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
  }
  while(vertAccel > APOGEE_ACCEL_THRESH)
 
 
  digitalWrite(DROGUE_EMATCH_PIN, HIGH);
  //Read 9-DOF data
  //Read BMP180 data
  //Read GPS data
  //Write data to Xbee
  //Write data to serial logger
  //Include extra statement in serial transmission to indicated when parachute was deployed
  
  
  //Main parachute deployment algorithm 
  //Read and transmit data from all sensors while rocketAltitude above MAIN_ALT_THRESH altitude
  //Send current HIGH to MAIN parachute e-match when rocketAltitude equal to or below MAIN_ALT_THRESH
  do
  {
    //Read 9-DOF data
    //Read BMP180 data
    //Read GPS data
    //Write data to Xbee
    //Write data to serial logger
  }
  while(rocketAltitude > MAIN_ALT_THRESH)
  
  
  digitalWrite(MAIN_EMATCH_PIN, HIGH);
  //Read 9-DOF data
  //Read BMP180 data
  //Read GPS data
  //Write data to Xbee
  //Write data to serial logger
  //Include extra statement in serial transmission to indicated when parachute was deployed
 
 
}
