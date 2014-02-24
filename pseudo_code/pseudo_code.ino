//Libraries

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#define GPSECHO  false


//Timer variable to be used throughout program
uint32_t timer = millis();

//Global variables and constants

float dofData[9] = {0,0,0,0,0,0,0,0,0}; //9 channels
float gpsData[10] = {0,0,0,0,0,0,0,0,0,0}; // CHANGE to suit number of required data fields 
float bmpData[3] = {0,0,0};  // Altitude  Temperature  Pressure

const int LED_PIN = 0;
const int LAUNCH_THRESH = 300; //500 ft altitude detected, switch from mode 1 to mode 2
const int DROGUE_EMATCH_PIN = 1; //Pin connected to drogue parachute e-match
const int MAIN_EMATCH_PIN = 2; //Pin connected to main parachute e-match
const int APOGEE_ACCEL_THRESH = 3; // Acceleration upper threshold for apogee detection
const int MAIN_ALT_THRESH = 1800; //Altitude lower threshold for main chute deployment (1800 ft.)


void setup()
{


//-----------------------------------------------------------------------------------------------------
//PIN INITIALIZATIONS

  pinMode(LED_PIN, OUTPUT);
  pinMode(DROGUE_EMATCH_PIN, OUTPUT);
  pinMode(MAIN_EMATCH_PIN, OUTPUT);
  

//-----------------------------------------------------------------------------------------------------  
//SERIAL PORT INITIALIZATIONS 
  
//Xbee ("Serial") and SD Logger ("Serial1") communicate at 9600 baud rate, while the GPS ("Serial2") uses 115200
  Serial.begin(115200); //GPS
  Serial1.begin(9600); //SD Logger
  Serial2.begin(9600); //Xbee  

//-----------------------------------------------------------------------------------------------------
//GPS INITIALIZATION

Adafruit_GPS GPS(&Serial1);
setupGPS()
  
//----------------------------------------------------------------------------------------------------- 
//BMP180 PRESSURE SENSOR INTIALIZATION
  
  Serial.println("BMP180 Pressure Sensor Test");
  Serial.println("")
  
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

//-----------------------------------------------------------------------------------------------------

}

void loop()
{
 
 //Variable declarations
 float rocketAltitude = 0;
  
 delay(500) // intial delay for all electronics
 

 
 //----------------------------------------------------------------------------------------------------- 
 //Rocket pre-launch algorithm
  do
  {
    //Read 9-DOF data
    getBMP(); //Read BMP180 data
    rocketAltitude = bmpData[0]; //Extract altitude from bmpData array
    getGPS(); //Read GPS data
    dataOut(); //Transmit data to SD logger, then Xbee
  }
  while(rocketAltitude<LAUNCH_THRESH) 
 
 
 
  //----------------------------------------------------------------------------------------------------- 
  //Drogue parachute deployment algorithm 
  //Read and transmit data from all sensors while vertAccel greater than APOGEE_ACCEL_THRESH
  //Send current HIGH to DROGUE parachute e-match when vertAccel less than or equal to APOGEE_ACCEL_THRESH
  do
  {
    //Read 9-DOF data
    getBMP(); //Read BMP180 data
    rocketAltitude = bmpData[0]; //Extract altitude from bmpData array
    getGPS(); //Read GPS data
    dataOut(); //Transmit data to SD logger, then Xbee
  }
  while(vertAccel > APOGEE_ACCEL_THRESH)
 
 
  digitalWrite(DROGUE_EMATCH_PIN, HIGH);
  //Read 9-DOF data
  getBMP(); //Read BMP180 data
  rocketAltitude = bmpData[0]; //Extract altitude from bmpData array
  getGPS(); //Read GPS data
  dataOut(); //Transmit data to SD logger, then Xbee
  //Include extra statement in serial transmission to indicated when parachute was deployed
  
  
  
  //----------------------------------------------------------------------------------------------------- 
  //Main parachute deployment algorithm 
  //Read and transmit data from all sensors while rocketAltitude above MAIN_ALT_THRESH altitude
  //Send current HIGH to MAIN parachute e-match when rocketAltitude equal to or below MAIN_ALT_THRESH
  do
  {
    //Read 9-DOF data
    getBMP(); //Read BMP180 data
    rocketAltitude = bmpData[0]; //Extract altitude from bmpData array
    getGPS(); //Read GPS data
    dataOut(); //Transmit data to SD logger, then Xbee
  }
  while(rocketAltitude > MAIN_ALT_THRESH)
  
  
  digitalWrite(MAIN_EMATCH_PIN, HIGH);
  //Read 9-DOF data
  getBMP(); //Read BMP180 data
  rocketAltitude = bmpData[0]; //Extract altitude from bmpData array
  getGPS(); //Read GPS data
  dataOut(); //Transmit data to SD logger, then Xbee
  //Include extra statement in serial transmission to indicated when parachute was deployed

 
}






//----------------------------------------------------------------------------------------------------- 
//CUSTOM FUNCTIONS HERE!!!








