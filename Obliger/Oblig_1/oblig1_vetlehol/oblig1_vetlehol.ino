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
  ledValue = false;

}

void loop() {
   if (Serial.available()) 
   { // If data is available to read,
    inputValue = Serial.read(); // read it and store it in val

    if (inputValue == '1' & !ledValue) 
    { // If 1 was received
      digitalWrite(LED_BUILTIN, HIGH);
      ledValue = true;
      Serial.print("1");
    }
    else if (inputValue == '1' & ledValue) {
      digitalWrite(LED_BUILTIN, LOW);
      ledValue = false;
      Serial.print("0");
    } 
    inputValue = '0';
   }
   delay(10); // Wait 10 milliseconds for next reading
}
