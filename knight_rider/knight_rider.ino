// LED variables
int pins[] = {2,3,4,5,6,7};
int count = 0;
float timer = 30;

// Resistor variables
int analogInput = 0;
int Vin = 5;
float Vout = 0;
float R1 = 1000;
float R2 = 0;

void setup() {
  // set all the pins for the LEDs to OUTPUT
  for (count=0; count<6; count++) {
    pinMode(pins[count], OUTPUT);
  }
  // start reading the analog signal for the resistance
  Serial.begin(9600);
}

void loop() {
  // flash left to right ---->>>
  for (count=0; count<5; count++) {
    // calculate resistance of LDR
    analogInput = analogRead(0);
    Vout = (analogInput * Vin)/1024.0;
    R2 = (R1 * ((Vin/Vout) - 1))/1000;
    // chase LEDs
    digitalWrite(pins[count], HIGH);
    delay(timer/R2);
    digitalWrite(pins[count+1], HIGH);
    delay(timer/R2);
    digitalWrite(pins[count], LOW);
    delay((timer/R2)*2);
  }

  // flash right to left <<<----
  for (count=5; count>0; count--){
    // calculate resistance of LDR
    analogInput = analogRead(0);
    Vout = (analogInput * Vin)/1024.0;
    R2 = (R1 * ((Vin/Vout) - 1))/1000;
    // chase LEDs
    digitalWrite(pins[count], HIGH);
    delay(timer/R2);
    digitalWrite(pins[count-1], HIGH);
    delay(timer/R2);
    digitalWrite(pins[count], LOW);
    delay((timer/R2)*2);
  }
}
