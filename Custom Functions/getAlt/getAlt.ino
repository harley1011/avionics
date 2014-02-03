    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
*/



float getAlt()
{
 // Get a new sensor event 
  sensors_event_t event;
  bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressure in hPa */
  //  Serial.print(event.pressure);
     
    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);
  //  Serial.print(temperature);
    

    /* Then convert the atmospheric pressure, SLP and temp to altitude    */
    /* Update this next line with the current SLP for better results      */
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
 //   Serial.print("Altitude:    "); 
   // Serial.print(bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature)); 
    float rocketAltitude = bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature);

  }
  else
  {
    Serial.println("BMP180 Pressure Sensor error");
  }
  return rocketAltitude
}


