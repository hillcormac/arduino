int pins[] = {2,3,4,5,6,7};
int count = 0;
float timer = 30;

void setup() {
  // set all the pins for the LEDs to OUTPUT
  for (count=0; count<6; count++) {
    pinMode(pins[count], OUTPUT);
  }
}

void loop() {
  // flash left to right ---->>>
  for (count=0; count<5; count++) {
    digitalWrite(pins[count], HIGH);
    delay(timer);
    digitalWrite(pins[count+1], HIGH);
    delay(timer);
    digitalWrite(pins[count], LOW);
    delay(timer*2);
  }

  // flash right to left <<<----
  for (count=5; count>0; count--){
    digitalWrite(pins[count], HIGH);
    delay(timer);
    digitalWrite(pins[count-1], HIGH);
    delay(timer);
    digitalWrite(pins[count], LOW);
    delay(timer*2);
  }
}
