import processing.serial.*;
int rectX = 20;
int rectY = 20;      // Position of square button
int rectSize = 140;     // Diameter of rect
color rectColor, baseColor;
color rectHighlight;
color currentColor;
boolean rectOver = false;
Serial myPort;
PFont parachuteLaunch;

void setup() {
  println(Serial.list());
  myPort = new Serial(this,Serial.list()[2], 9600);
  size(640, 360);
  rectColor = color(0);
  rectHighlight = color(51);
  parachuteLaunch = createFont("Arial",16,true);
  
}

void draw() {
  background(255);
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
  for( int = 0; 
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

