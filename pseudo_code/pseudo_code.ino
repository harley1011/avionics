//Libraries

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GPS.h>

//Timer variable to be used throughout program
uint32_t timer = millis();

//Global variables and constants

float dofData[9] = {0,0,0,0,0,0,0,0,0}; //9 channels
float gpsData[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 
float bmpData[3] = {0,0,0}  // Altitude  Temperature  Pressure

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
  Serial.begin(9600); //Xbee
  Serial1.begin(9600); //SD Logger
  Serial2.begin(115200); //GPS  

//-----------------------------------------------------------------------------------------------------
//GPS INITIALIZATION

Adafruit_GPS GPS(&Serial1);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false

// 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

//EXPERIMENT WITH DIFFERENT DATA OUTPUTS BELOW!
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  
//EXPERIMENT WITH DIFFERENT UPDATE RATES TO SEE WHAT WE CAN HANDLE
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz


//WHAT IS THIS?
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);

//WHAT IS THIS?
  // Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
  
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








