/*
  Precode for IN1080 - Assignment 1

  https://www.uio.no/studier/emner/matnat/ifi/IN1080/ 
*/

char inputValue; // Data received from the serial port
bool ledValue; // True if HIGH, False if LOW

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // Set pin as OUTPUT
  Serial.begin(9600); // Start serial communication at 9600 bps
  ledValue = false; // True if LED on (HIGH), false if LED off (LOW)

}

void loop() {
   if (Serial.available()) 
   { // If data is available to read,
    inputValue = Serial.read(); // read it and store it in val

    // If 1 was received
    if (inputValue == '1' & !ledValue) { // Will turn LED to 'HIGH' if 'LOW' 
      digitalWrite(LED_BUILTIN, HIGH);
      ledValue = true;
      Serial.print("1");
    }
    else if (inputValue == '1' & ledValue) { // Will turn LED to 'LOW' if 'HIGH' 
      digitalWrite(LED_BUILTIN, LOW);
      ledValue = false;
      Serial.print("0");
    } 
    inputValue = '0';
   }
   delay(10); // Wait 10 milliseconds for next reading
}
