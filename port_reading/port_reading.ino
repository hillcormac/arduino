int greenPin = 10;
int redPin = 11;
byte firstBit;
byte secondBit;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  for (firstBit = B10000000, secondBit = B01000000;
  firstBit > 2, secondBit > 2; firstBit>>=1, secondBit>>=1) {
     if ((PIND & firstBit) && (PIND & secondBit)) {
       digitalWrite(redPin, HIGH);
     } else {
       digitalWrite(redPin, LOW);
     }
     if ((~PIND & firstBit) && (~PIND & secondBit)) {
       digitalWrite(greenPin, HIGH);
     } else {
       digitalWrite(greenPin, LOW);
     }
    }
}
