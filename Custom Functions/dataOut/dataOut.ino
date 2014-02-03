//This is a function that will output all of the data from the GPS sensor (specify model),
//the BMP180 pressure sensor, and the 9-DOF sensor stick to the OpenLog SD logger first
//and then the Xbee Pro 900
// Xbee: "Serial"
// OpenLog: "Serial1"

//IMPORTANT: This code needs to be updated to work with OpenLog serial to SD logger. 
//Commands need to be added to control OpenLog ( https://github.com/sparkfun/OpenLog.wiki.git )


void dataOut()
{
  
  //Send all 9-DOF data, 10 channels
  for(int i = 0; i<10; i++)
  {
  Serial1.print(dofData[i]);
  Serial1.print("    ");
  Serial.print(dofData[i]
  Serial.print("    ");
  }
  
  //Send all BMP180 data, 4 channels
  for(int i = 0; i<4; i++)
  {
  Serial1.print(bmpData[i]);
  Serial1.print("    ");
  Serial.print(bmpData[i]);
  Serial.print("    ");
  }
  
  //Send all GPS data, 16 channels
  for(int i =0; i<16; i++)
  {
  Serial1.print(gpsData[i]);
  Serial1.print("    ");
  Serial.print(gpsData[i]);
  Serial.print("    ");
  }
  
}
