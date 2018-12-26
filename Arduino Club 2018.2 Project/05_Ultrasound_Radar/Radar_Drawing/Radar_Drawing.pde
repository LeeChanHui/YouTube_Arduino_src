import processing.serial.*;
 
Serial myPort;
String myString = null;
int angle = 0;
int distance = 0;
 
void setup(){
  size(1200, 700);
  background(0);
  myPort = new Serial(this, "COM14", 9600);
}
 
void draw(){
  noStroke();
  fill(0,7);
  rect(0,0,width,height);
  drawRader();
  drawLine();
  drawObject();
}
 
void serialEvent(Serial p){
  try{
    myString = p.readStringUntil('.');
    String[] list = split(myString, ',');
    angle = int(list[0]);
    distance = int(list[1].replace(".",""));
  }catch(Exception e){
    print(e);
  }
}
 
void drawRader(){
  pushMatrix();
  translate(width/2, height);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
   
  // draw the arc lines
  arc(0, 0, width, width, PI, TWO_PI);
  arc(0, 0, width*2/3, width*2/3, PI, TWO_PI);
  arc(0, 0, width*1/3, width*1/3, PI, TWO_PI);
   
  // draw the angle lines
  line(0, 0, width/2*cos(radians(30)), -width/2*sin(radians(30)));
  line(0, 0, width/2*cos(radians(60)), -width/2*sin(radians(60)));
  line(0, 0, width/2*cos(radians(90)), -width/2*sin(radians(90)));
  line(0, 0, width/2*cos(radians(120)), -width/2*sin(radians(120)));
  line(0, 0, width/2*cos(radians(150)), -width/2*sin(radians(150)));
   
  // draw text
  textSize(15);
  fill(98, 245, 31);
  textAlign(RIGHT);
  text("10cm", width*1/6, 0);
  text("20cm", width*2/6, 0);
  text("30cm", width*3/6, 0);
 
  popMatrix();
}
 
void drawLine(){
  pushMatrix();
  translate(width/2, height);
  strokeWeight(4);
  stroke(98, 245, 31);
  line(0, 0, width/2*cos(radians(angle)), -width/2*sin(radians(angle)));
  popMatrix();
}
 
void drawObject(){
  pushMatrix();
  translate(width/2, height);
  strokeWeight(4);
  stroke(255, 10, 10); // red color
  float d = (width/2.0/30.0)*(float)distance;
   
  if( d < width/2)
    line(d*cos(radians(angle)), -d*sin(radians(angle)), width/2*cos(radians(angle)), -width/2*sin(radians(angle)));
  popMatrix();
}
