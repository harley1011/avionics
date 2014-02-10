import processing.serial.*;
int rectSwitchX = 20;
int rectSwitchY = 410;
int rectSwitchSizeX = 70;
int rectSwitchSizeY = 30;
color rectSwitchColor;
boolean rectSwitchOver = false;
int rectX = 20;
int rectY = 450;      // Position of square button
int rectSizeX = 180;// Diameter of rect
int rectSizeY = 30;
color rectColor, baseColor;
color rectHighlight;
color currentColor;
color greenColor = #33FF33;
boolean rectOver = false;
Serial myPort;
PFont font = createFont("Courier",16,true);

void setup() {
  println(Serial.list());
 // myPort = new Serial(this,Serial.list()[0], 9600);
  size(700, 500);
  rectSwitchColor = color(#D0D0D0 );
  rectColor = color(#D0D0D0 );
  rectHighlight = color(51);
  
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
   rect(rectX, rectY, rectSizeX, rectSizeY);

    if(rectSwitchOver){
    fill(rectHighlight);
  }else{
    fill(rectColor);
  }
  rect(rectSwitchX, rectSwitchY,rectSwitchSizeX,rectSwitchSizeY);
  textFont(font,16);
  fill(255,0,0);
  text("Enable", rectSwitchX + 5,rectSwitchY +20);
  text("Deploy parachute!", rectX + 5,rectY +20);
  listSensorsOnline ();
  readSensorDataAndDraw();
}
void listSensorsOnline ()
{
  String[] sensorsNameList = {"Accelerometer", "Gyroscope", "Barometric","GPS"}; 
  textFont(font);
  fill(greenColor);
  text("Sensors Status: Good", 20, 80);
  for ( int i = 0; i < sensorsNameList.length; i++)
  {
    text(sensorsNameList[i] + ":", 20, 100 + i*20 );
    text("Online", 180, 100 + i*20 );
  }
    createText(font,greenColor,"Rocket Status: Launch mode",20,50);
}
void readSensorDataAndDraw()
{

  int xCord = 310;
  createText(font, greenColor,"Sensor Data: ", xCord - 10,50);
  fill(0);
  stroke(greenColor);
  rect(xCord - 10, 55, 350, 400);
  createText(font, greenColor,"Acceleration(m/s^2):", xCord,80);
  createText(font, greenColor,  "X: 0    Y: 0    Z: 0", xCord+ 20,100);
  createText(font, greenColor,"Velocity(m/s):", xCord,130);
  createText(font, greenColor,  "X: 0    Y: 0    Z: 0", xCord+ 20,150);
    createText(font, greenColor,"GPS coordinates:", xCord,180);
  createText(font, greenColor,  "X: 0    Y: 0    Z: 0", xCord + 20,200);
      createText(font, greenColor,"Orientation:", xCord,230);
  createText(font, greenColor,"Yaw: 0    Pitch: 0    Roll: 0", xCord + 20,250);
  createText(font, greenColor,  "Max altitude:     0m", xCord,280);
  createText(font, greenColor,  "Current altitude: 0m", xCord,310);
    createText(font, greenColor,"Air pressure:     1atm", xCord,340);
  
  
}
void createText( PFont font, color textColor,String text, int x, int y)
{
  textFont(font);
  fill(textColor);
  text(text, x, y );
}
void update(int x, int y) {
   if ( overRect(rectX, rectY, rectSizeX, rectSizeY) ) {
    rectOver = true;
  } else {
    rectOver = false;
  }
  if(overSwitchRect(rectSwitchX,rectSwitchY,rectSwitchSizeX, rectSwitchSizeY)) {
    rectSwitchOver = true;
  }
  else {
    rectSwitchOver = false;
  }
}

void mousePressed() {
  if (rectOver) {
    myPort.write("54321");
  }
  if(rectSwitchOver){
    rectSwitchColor = "#FF0000";
  }
}
boolean overSwitchRect(int x, int y, int width, int height)
{
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
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

