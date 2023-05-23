#include <IRremote.h>
#define latchPin 8
#define clockPin 12
#define dataPin 2
#define receiverPin 11

IRrecv irrecv(receiverPin);
decode_results results;
byte midByte;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&results)) {
    midByte = results.value >> 8;
    if (midByte != 0xff) {
      Serial.println(midByte, BIN);
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, midByte);
      digitalWrite(latchPin, HIGH);
    }
    irrecv.resume();
  }
}
