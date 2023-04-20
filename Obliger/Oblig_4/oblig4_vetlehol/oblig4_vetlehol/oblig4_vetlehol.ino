// Trafikklys for bil
const int bilGrontLysPin = 11;
const int bilGultLysPin = 12;
const int bilRoedtLysPin = 13;

// Trafikklys for fotgjenger
const int fotgjengerGrontLysPin = 4;
const int fotgjengerRoedtLysPin = 5;
const int fotgjengerBryterPin = 2;
const int fotgjengerBlaaLysPin = 3;
const int fotgjengerPiezoPin = 10;

// Tidsvariabler
unsigned long startTid;
unsigned long tidSidenTrykk;

// Statusvariabler
bool bilGrontLysStatus = true;
bool fotgjengerRoedtLysStatus = true;
bool fotgjengerBryterStatus = false;

void setup() {
  pinMode(bilGrontLysPin, OUTPUT);
  pinMode(bilGultLysPin, OUTPUT);
  pinMode(bilRoedtLysPin, OUTPUT);
  pinMode(fotgjengerGrontLysPin, OUTPUT);
  pinMode(fotgjengerRoedtLysPin, OUTPUT);
  pinMode(fotgjengerBryterPin, INPUT_PULLUP);
  pinMode(fotgjengerBlaaLysPin, OUTPUT);
  pinMode(fotgjengerPiezoPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(fotgjengerBryterPin), buttonInterrupt, FALLING);
}

void buttonInterrupt() {
  fotgjengerBryterStatus = true;
  startTid = millis();
}

void loop() {
  // Dersom ingen har trykket paa knappen.
  if (!fotgjengerBryterStatus) {
    // Trafikklys for bil
    digitalWrite(bilGrontLysPin, HIGH);
    digitalWrite(bilRoedtLysPin, LOW);
    digitalWrite(bilGultLysPin, LOW);
    
    // Trafikklys for fotgjenger
    digitalWrite(fotgjengerGrontLysPin, LOW);
    digitalWrite(fotgjengerRoedtLysPin, HIGH);
    tone(fotgjengerPiezoPin, 100, 500);
    delay(500);
    noTone(fotgjengerPiezoPin);
    delay(500);
  }
  // Hvis noen har trykket på bryteren
  else {
    tidSidenTrykk = millis() - startTid;
    // Trafikklys for bil og fotgjenger når knapp er blitt trykket
    if (tidSidenTrykk < 4000) {
      digitalWrite(fotgjengerGrontLysPin, LOW);
      digitalWrite(fotgjengerRoedtLysPin, LOW);
      digitalWrite(fotgjengerBlaaLysPin, HIGH);
    }

    // Etter 2 sek går billys til gult.
    if (tidSidenTrykk >= 2000 && tidSidenTrykk < 3000) {
      digitalWrite(bilGrontLysPin, LOW);
      digitalWrite(bilGultLysPin, HIGH);
      digitalWrite(bilRoedtLysPin, LOW);
    } 
    // 1 sek etter billys går til gult, billys går til rødt.
    if (tidSidenTrykk >= 3000 && tidSidenTrykk < 4000) {
      digitalWrite(bilGrontLysPin, LOW);
      digitalWrite(bilGultLysPin, LOW);
      digitalWrite(bilRoedtLysPin, HIGH);      
    }
    // 1 sek etter billys går til rødt, blir det grønt lys for fotgjengere.
    if (tidSidenTrykk >= 4000 && tidSidenTrykk < 10000) {
      digitalWrite(fotgjengerGrontLysPin, HIGH);
      digitalWrite(fotgjengerRoedtLysPin, LOW);
      digitalWrite(fotgjengerBlaaLysPin, LOW);
      tone(fotgjengerPiezoPin, 100);  
      delay(125);
      noTone(fotgjengerPiezoPin);
      delay(125);


    }
    // Når det har vært grønt for fotgjenger i 6 sekunder begynner det grønne lyset å blinke.
    // Deretter går den tilbake til vanlig.
    if (tidSidenTrykk >= 10000) {
      digitalWrite(fotgjengerGrontLysPin, LOW);
      delay(500);
      digitalWrite(fotgjengerGrontLysPin, HIGH);
      delay(500); 
      digitalWrite(fotgjengerGrontLysPin, LOW);
      delay(500);
      digitalWrite(fotgjengerGrontLysPin, HIGH);
      delay(500);
      digitalWrite(fotgjengerGrontLysPin, LOW);  
      delay(500);
      digitalWrite(fotgjengerGrontLysPin, HIGH);
      delay(500);
      digitalWrite(fotgjengerGrontLysPin, LOW);
      digitalWrite(fotgjengerRoedtLysPin, HIGH);
      digitalWrite(fotgjengerBlaaLysPin, LOW);

      digitalWrite(bilGrontLysPin, LOW);
      digitalWrite(bilGultLysPin, HIGH);
      digitalWrite(bilRoedtLysPin, LOW);  
      delay(1000);
      fotgjengerBryterStatus = false;
    }
  }
}

