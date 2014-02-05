// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
//
// If you're using a GPS module:
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3
//
//
// NOTE: "gpsData" array must be declared outside of this function or as a global variable
// Be sure to clear the gpsData array after each cycle through void loop() function



float getGPS[]()
{
  

//IF USING INTERRUPT, UNCOMMENT BELOW:
//-----------------------------------------------------------------------------------------------------
//    OCR0A = 0xAF;
//    TIMSK0 |= _BV(OCIE0A);
//    usingInterrupt = true;
//-----------------------------------------------------------------------------------------------------


//IF NOT USING INTERRUPT, UNCOMMENT BELOW:
//-----------------------------------------------------------------------------------------------------
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
//-----------------------------------------------------------------------------------------------------


  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();


//EXTREMELY USEFUL GPS FUNCTIONS!

gpsData[0] = GPS.hour;
gpsData[1] = GPS.minute;
gpsData[2] = GPS.seconds;
gpsData[3] = GPS.milliseconds;

//May be unnecessary
gpsData[4] = GPS.day;
gpsData[5] = GPS.month;
gpsData[6] = GPS.year;

gpsData[7] = GPS.fix;  //Boolean 1 if there is a satellite fix, 0 if there isn't
gpsData[8] = GPS.fixquality;
gpsData[9] = GPS.latitude;
gpsData[10] = GPS.longitude;
gpsData[11] = GPS.speed;  //Measured in knots
gpsData[12] = GPS.angle;
gpsData[13] = GPS.altitude;  //Measured in centimeters
gpsData[14] = GPS.satellites;  //Number of satellites
gpsData[15] = timer;

}
