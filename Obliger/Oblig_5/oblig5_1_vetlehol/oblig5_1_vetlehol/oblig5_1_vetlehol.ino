#include <Servo.h>

Servo myservo;
int analogPin = A0;
int servoValue;
int analogValue;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(analogPin);
  servoValue = map(analogValue, 0, 1023, 0, 180);
  Serial.println(servoValue);
  myservo.write(servoValue);
}
