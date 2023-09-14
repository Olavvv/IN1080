const int potPin = A5; // analog pinne for å lese potensiometer
const int pwmPin = 10; // pinne for å gi ut PWM-signal
unsigned long prevMillis = 0;

const long frekvens = 100; 
const long periode = 10;
bool motorStatus = false;


void setup() {
  pinMode(pwmPin, OUTPUT); // pwmPin settes til output
  Serial.begin(9600); 
}

void loop() {
  long currentMillis = millis();
  int dutyCycle = analogRead(potPin) / 4; // duty cycle settes til 0-255 (0-1023 / 4)

  // Finner tiden motoren skal være på og av.
  long tidPaa = (dutyCycle/frekvens);
  long tidAv = (periode - tidPaa);

  if (currentMillis - prevMillis >= tidAv && !motorStatus) {
    prevMillis = currentMillis;
    digitalWrite(pwmPin, HIGH);
    motorStatus = true;
  }
  else if (currentMillis - prevMillis >= tidPaa && motorStatus) {
    prevMillis = currentMillis;
    digitalWrite(pwmPin, LOW);
    motorStatus = false;
  }
}