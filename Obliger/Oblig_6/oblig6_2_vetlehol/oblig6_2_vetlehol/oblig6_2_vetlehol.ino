// some useful consts
const int DUTY_MAX = 255;
const int ENCODER_MAX = 1024;
const int SLACK = 15;

// TODO: define pins as consts
const int potPin = A5;
const int motPin = A0;
const int pwmPin = 10;


// some useful variables
double errorSum = 0;
double errorLast = 0;
const long frekvens = 100; //Hz
const long periode = 10; //ms
bool motorStatus = false;
long prevMillis = 0; //ms

// TODO: define other relevant variable(s)

// Default PID gains
double Kp = 1.0;
double Ki = 0.00;
double Kd = 0.0;

void setup() {
  // TODO: set up pins here
  pinMode(pwmPin, OUTPUT); // pwmPin settes til output
  Serial.begin(9600); // start the serial connection
}

void loop() {
  readPidGainsFromProcessing(); // read PID gains from Processing

  // TODO: read target position from the reference potentiometer
  int targetPos = analogRead(potPin);

  // TODO: read motor position from the "encoder" potentiometer
  int motorPos = analogRead(motPin);

  motorController(targetPos, motorPos);
}

// Function to read the PID gains from the Processing code
void readPidGainsFromProcessing() {
  if (Serial.available()) {
    String inputValue = Serial.readString();
    char type = inputValue.charAt(0);
    double gain = inputValue.substring(inputValue.indexOf(' '), inputValue.length()).toDouble();
    switch (type) {
      case 'p': 
        Kp = gain;
        break;
      case 'i':
        Ki = gain;
        errorSum = 0;
        break;
      case 'd':
        Kd = gain;
        break;
    }
  }
}

// Function that implements motor control
void motorController(int targetPos, int currentPos) {

  double error = targetPos - currentPos;

  // if error is less than the encoder slack, do not actuate the motor
  if(error < SLACK && error > 0 - SLACK){
    pwm(0);
    errorSum = 0;
    return;
  }
  
  // TODO: update errorSum
  errorSum += error;

  double command = pidController(Kp, Ki, Kd, error, errorSum, errorLast); // call PID controller

  // integrator anti-windup (do not accumulate sum of errors when output is saturated)
  if(command > ENCODER_MAX){
    command = ENCODER_MAX;
    errorSum = errorSum - error;
  } else if(command < -ENCODER_MAX){
    command = -ENCODER_MAX;
    errorSum = errorSum - error;
  }

  int dutyCycle = map(command, -ENCODER_MAX, ENCODER_MAX, -DUTY_MAX, DUTY_MAX); // map command to duty cycle

  pwm(dutyCycle);

  // TODO: update errorLast
  errorLast = error; 
}

// Function that implements a PID controller
double pidController(double Kp, double Ki, double Kd, double error, double errorSum, double errorLast) {
  // TODO: implement the PID controller using the variables Kp, Ki, Kd, error, errorSum and errorLast
  double P = Kp*error;
  double I = Ki*errorSum;
  double D = Kd*(error - errorLast);
  double output = P + I + D;
  //       hint 1: the integral component operates on the sum of errors (errorSum)
  //       hint 2: the derivative component operates on the error from the previous loop (errorLast)
  return output; 
}

// Function that implements PWM
void pwm(double dutyCycle){
  // TODO: copy over your function from the previous task
  long currentMillis = millis();

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