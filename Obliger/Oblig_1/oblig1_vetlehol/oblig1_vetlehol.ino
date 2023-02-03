char inputvalue; // Data received from the serial port

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // Set pin as OUTPUT
  Serial.begin(9600); // Start serial communication at 9600 bps

}

void loop() {
   if (Serial.available()) 
   { // If data is available to read,
    inputvalue = Serial.read(); // read it and store it in val


    if (inputvalue == "1") 
    { // If 1 was received
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("0"); //Insert your code in this block
    } 
   }
   delay(10); // Wait 10 milliseconds for next reading
}