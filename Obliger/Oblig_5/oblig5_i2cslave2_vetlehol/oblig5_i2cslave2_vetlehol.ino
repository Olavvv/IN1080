/*
  Precode for IN1080 - Assignment 1

  https://www.uio.no/studier/emner/matnat/ifi/IN1080/ 
*/
#include <Wire.h>

const byte ADDRESS = 2;

char recievedValue; // Data received from the serial port
bool ledValue; // True if HIGH, False if LOW

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // Set pin as OUTPUT
  Serial.begin(9600); // Start serial communication at 9600 bps
  ledValue = false; // True if LED on (HIGH), false if LED off (LOW)
  Wire.begin(ADDRESS);
  Wire.onRecieve(recieveEvent); // Kaller recieveEvent funksjon naar data mottas.


}

void loop() {
}

void recieveEvent(int bytesRecieved) {
  while (Wire.available()) {
    recievedValue = Wire.read();
    if (recievedValue == 1 && !ledValue) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("Led for slave 2 skrudd paa.");
      ledValue = true;

    } else if (recievedValue == 1 && ledValue) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("Led for slave 2 skrudd av.");
      ledValue = false;
    }
  }
}
