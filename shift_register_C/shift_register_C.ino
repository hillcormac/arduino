#include <IRremote.h>
#define latchPin 8
#define clockPin 12
#define receiverPin 11

IRrecv irrecv(receiverPin);
decode_results results;
byte lsByte;

void shiftOut(uint8_t shiftClockPin, uint8_t bitOrder, uint8_t val) {
  for (int i = 0; i < 8; i++) {
    if (bitOrder == LSBFIRST) {
      (!!(val & (1 << i))) ? PORTD = B00000100 : PORTD = B00000000;
    } else {
      (!!(val & (1 << (7-i)))) ? PORTD = B00000100 : PORTD = B00000000;
      
    }
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(shiftClockPin, LOW);
  }
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(PD2, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&results)) {
    lsByte = lowByte(results.value);
    if (lsByte != 0xff) {
      Serial.println(lsByte, BIN);
      digitalWrite(latchPin, LOW);
      shiftOut(clockPin, LSBFIRST, lsByte);
      digitalWrite(latchPin, HIGH);
    }
    irrecv.resume();
  }
}
