import processing.serial.*;
int rectX = 20;
int rectY = 20;      // Position of square button
int rectSize = 140;     // Diameter of rect
color rectColor, baseColor;
color rectHighlight;
color currentColor;
color greenColor = #33FF33;
boolean rectOver = false;
Serial myPort;
PFont parachuteLaunch;

void setup() {
  println(Serial.list());
  myPort = new Serial(this,Serial.list()[0], 9600);
  size(800, 500);
  rectColor = color(#D0D0D0 );
  rectHighlight = color(51);
  parachuteLaunch = createFont("Arial",16,true);
  
}

void draw() {
  background(0);
  update(mouseX, mouseY);
  if (rectOver) {
    fill(rectHighlight);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectX, rectY, rectSize, rectSize/3);
  textFont(parachuteLaunch,16);
  fill(255,0,0);
  text("Deploy parachute!", 25,50);
  listSensorsOnline ();

  readSensorDataAndDraw();
}
void listSensorsOnline ()
{
  String[] sensorsNameList = {"Accelerometer", "Gyroscope", "Barometric","GPS"}; 
  PFont sensorOnline = createFont("Arial",16,true);
  textFont(sensorOnline);
  fill(greenColor);
  text("Sensors Status: Good", 200, 80);
  for ( int i = 0; i < sensorsNameList.length; i++)
  {
    text(sensorsNameList[i] + ": Online", 200, 100 + i*20 );
  }
    createText(sensorOnline,greenColor,"Rocket Status: Launch mode",200,50);
}
void readSensorDataAndDraw()
{
  PFont sensorOnline = createFont("Arial",16,true);
  int xCord = 430;
  createText(sensorOnline, greenColor,"Sensor Data: ", xCord - 10,50);
  fill(0);
  stroke(greenColor);
  rect(xCord - 10, 55, 350, 400);
  createText(sensorOnline, greenColor,"Acceleration:", xCord,80);
  createText(sensorOnline, greenColor,  "X: 0m/s^2    Y: 0m/s^2    Z: 0m/s^2", xCord+ 20,100);
  createText(sensorOnline, greenColor,"Velocity:", xCord,130);
  createText(sensorOnline, greenColor,"X: 0m/s      Y: 0m/s      Z: 0m/s", xCord+ 20,150);
    createText(sensorOnline, greenColor,"GPS coordinates:", xCord,180);
  createText(sensorOnline, greenColor,"X: 0         Y: 0         Z: 0", xCord + 20,200);
  createText(sensorOnline, greenColor,"Max altitude: 0m", xCord,230);
  createText(sensorOnline, greenColor,"Current altitude: 0m", xCord,260);
    createText(sensorOnline, greenColor,"Air pressure: 1atm", xCord,290);
  
  
}
void createText( PFont font, color textColor,String text, int x, int y)
{
  textFont(font);
  fill(textColor);
  text(text, x, y );
}
void update(int x, int y) {
   if ( overRect(rectX, rectY, rectSize, rectSize/2) ) {
    rectOver = true;
  } else {
    rectOver = false;
  }
}

void mousePressed() {
  if (rectOver) {
    myPort.write("54321");
  }
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

