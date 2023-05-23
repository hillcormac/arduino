int num;
int numCount;
unsigned long delayTime = 0;
int timer = 10000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lottoNums[6];
  int numCount = sizeof(lottoNums)/sizeof(int);

  Serial.print("Lotto Numbers: ");
  for (int i=0; i < numCount; i++) {
    num = random(1, 42);
    for (int j=0; j < numCount; j++) {
      if (lottoNums[j] == num) {
        num = random(1, 42);
        j = 0;
      }
    }
    lottoNums[i] = num;
    Serial.print(num);
    Serial.print(" ");
  }
  Serial.println();
  delayTime = millis();
  while (millis() < delayTime + timer) {}
}
