int analogInput = 0;
int Vin = 5;
float Vout = 0;
float R1 = 1000;
float R2 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  analogInput = analogRead(0);
  Vout = (analogInput * Vin)/1024.0;
  R2 = R1 * ((Vin/Vout) - 1);
  Serial.print("AnalogInput: ");
  Serial.println(R2);
  delay(1000);
}
