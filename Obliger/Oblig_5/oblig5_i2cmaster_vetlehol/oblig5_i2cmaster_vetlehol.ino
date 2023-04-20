/*
  Precode for IN1080 - Assignment 1

  https://www.uio.no/studier/emner/matnat/ifi/IN1080/ 
*/
#include <Wire.h>
const byte ADDRESS1 = 1;
const byte ADDRESS2 = 2;

char inputValue; // Data received from the serial port
int clickCounter = 0; 


void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // starter I2C kommunikasjon
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
   if (Serial.available()) 
   { // If data is available to read,
    inputValue = Serial.read(); // read it and store it in val

    // Haandterer museklikk
    if (inputValue == '1') { 
      clickCounter++;
      if (clickCounter % 2 == 1) {
        sendToRegister(ADDRESS1);
      } else {
        sendToRegister(ADDRESS2);
      }
    }
    inputValue = '0';
   }
   delay(10); // Wait 10 milliseconds for next reading
}

void sendToRegister(byte address) {
  Wire.beginTransmission(address);
  Wire.write(1);
  Wire.endTransmission();
}