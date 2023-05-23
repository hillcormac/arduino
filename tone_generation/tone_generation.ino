#define DELAY(note) ((1.0/note) * 0.5 * 1000000)
#define MIDDLE_C 261.63
#define D 293.66
#define E 329.63
#define F 349.23
#define G 392.00
#define A 440.00
#define B 493.88
#define HIGH_C 1046.50

int middleNotes[] = {
  A, B, MIDDLE_C, D, E, F, G
};

int buzzerPin = 8;
char input;

// play specified note
void playNote(int note) {
  digitalWrite(buzzerPin, HIGH);
  delayMicroseconds(DELAY(note));
  digitalWrite(buzzerPin, LOW);
  delayMicroseconds(DELAY(note));
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // start reading from serial monitor
  if (Serial.available()) {
    input = Serial.read();
    int intInput = (int)input;
    // if the input ASCII is space, uppercase C (HIGH_C),
    // or from a-g (all other notes as shown in middleNotes array) 
    if (intInput == 32 || intInput == 67 || intInput >= 97 && intInput <= 103) {
      // if space, silence for a second
      if (intInput == 32) {
        digitalWrite(buzzerPin, LOW);
        delay(1000);
      // if uppercase C, play HIGH_C
      } else if (intInput == 67){
        playNote(HIGH_C);
      // if other value from a-g, search through array of notes,
      // and play note once found
      // -97 to align ASCII with position in the middleNotes array
      } else {
        intInput -= 97;
        for (int i = 0; i < middleNotes[intInput]; i++) {
          playNote(middleNotes[intInput]);
        }
      }
    } 
  }
}
