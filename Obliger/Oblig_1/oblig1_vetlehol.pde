/*
  Precode for IN1080 - Assignment 1

  https://www.uio.no/studier/emner/matnat/ifi/IN1080/ 
*/

import processing.serial.*;  

Serial myPort;  // Create object from Serial class
PImage img;

void setup() {
  size(662,481);                      //make our canvas 662 x 481 pixels big
  img = loadImage("fig/Arduino_uno.png"); //import an image of Arduino UNO
  image(img,0,0);                     //place image on canvas
  fill(0);                            //text color            
  textSize(20);                       //font size
  
  text("Velkommen til IN1080! Trykk på bildet for å blinke med LED.",40,30);//inserting text on canvas
  
  String portName = Serial.list()[0];//change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);//set up serial
}

void draw() {
  if (mousePressed == true) { //if we clicked in the window
    myPort.write("1");        //send a 1
    delay(100);               //delay to remove double clicking
    
    drawLed(myPort.readString());
  }
} 

void drawLed(String ledStatus) {
   if (ledStatus != null ) {
     println(ledStatus); 
     
     if (ledStatus.equals("0")) {
       fill(255);
     } else if (ledStatus.equals("1")) {
       fill(36,253,36);
     }
     square(280, 135, 10);
   }
}
