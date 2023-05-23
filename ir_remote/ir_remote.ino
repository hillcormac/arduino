#include <IRremote.h>

int receiverPin = 11;
IRrecv irrecv(receiverPin);
decode_results results;

unsigned long int hexValues[] = {
  0xff6897, 0xff30cf, 0xff18e7, 0xff7a85, 0xff10ef, 
  0xff38c7, 0xff5aa5, 0xff42bd, 0xff4ab5, 0xff52ad
};

int decValues[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    for (int i=0; i < 10; i++) {
      if (results.value == hexValues[i]) {
        Serial.println(decValues[i]);
        break;
      }
    }
    irrecv.resume();
  }
}
