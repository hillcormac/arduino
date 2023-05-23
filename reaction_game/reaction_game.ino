int startButton = 10;
int playerOneButton = 2;
int playerTwoButton = 7;

int playerOneGreen = 8;
int playerOneRed = 9;
int playerTwoGreen = 12;
int playerTwoRed = 13;
int buzzerPin = 11;

int startTime;
int delayStartTime;
int playerOneMillis = 0;
int playerTwoMillis = 0;
bool roundRunning = true;
bool earlyPress = false;

void setup() {
  Serial.begin(9600);
  pinMode(playerOneButton, INPUT_PULLUP);
  pinMode(playerTwoButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(playerOneGreen, OUTPUT);
  pinMode(playerOneRed, OUTPUT);
  pinMode(playerTwoGreen, OUTPUT);
  pinMode(playerTwoRed, OUTPUT);
}

void loop() {
  if (digitalRead(startButton) == LOW) {
    int playerOneScore = 0;
    int playerTwoScore = 0;
    Serial.println("GAME START!\n===========");
    
    for (int roundCount=0; roundCount < 3; roundCount++) {
      roundRunning = true;
      earlyPress = false;
      playerOneMillis = 0;
      playerTwoMillis = 0;     
      Serial.print("ROUND ");
      Serial.println(roundCount+1);
      int timer = random(0, 11);
      
      delayStartTime = millis();
      while (millis() < delayStartTime + (timer*1000)) {
        if (digitalRead(playerOneButton) == LOW) {
          Serial.println("Player 1 pressed their button too early, Player 2 wins\n===========");
          playerTwoScore += 1;
          digitalWrite(playerTwoGreen, HIGH);
          digitalWrite(playerOneRed, HIGH);
          earlyPress = true;
          break;
        }
        if (digitalRead(playerTwoButton) == LOW) {
          Serial.println("Player 2 pressed their button too early, Player 1 wins\n===========");
          playerOneScore += 1;
          digitalWrite(playerOneGreen, HIGH);
          digitalWrite(playerTwoRed, HIGH);
          earlyPress = true;
          break;
        }
      }
      if (earlyPress == true) {
        delay(5000);
        digitalWrite(playerOneGreen, LOW);
        digitalWrite(playerTwoRed, LOW);
        digitalWrite(playerOneRed, LOW);
        digitalWrite(playerTwoGreen, LOW);
        continue;
      }
      
      tone(buzzerPin, 1000);
      startTime = millis();
      
      while(roundRunning) {
        if (digitalRead(playerOneButton) == LOW && playerOneMillis == 0) {
          playerOneMillis = millis();
        }
        if (digitalRead(playerTwoButton) == LOW && playerTwoMillis == 0) {
          playerTwoMillis = millis();
        }
        if (playerOneMillis != 0 && playerTwoMillis != 0) {
          roundRunning = false;
          noTone(buzzerPin);
        }
      }

      if (playerOneMillis < playerTwoMillis) {
        digitalWrite(playerOneGreen, HIGH);
        digitalWrite(playerTwoRed, HIGH);
        Serial.print("ROUND WINNER: Player 1, TIME: ");
        Serial.print(playerOneMillis - startTime);
        Serial.print("ms, DIFFERENCE: ");
        Serial.print(playerTwoMillis - playerOneMillis);
        Serial.println("ms\n===========");
        playerOneScore += 1;
      }
      else if (playerTwoMillis < playerOneMillis) {
        digitalWrite(playerTwoGreen, HIGH);
        digitalWrite(playerOneRed, HIGH);
        Serial.print("ROUND WINNER: Player 2, TIME: ");
        Serial.print(playerTwoMillis - startTime);
        Serial.print("ms, DIFFERENCE: ");
        Serial.print(playerOneMillis - playerTwoMillis);
        Serial.println("ms\n===========");
        playerTwoScore += 1;
      }
      delay(5000);
      digitalWrite(playerOneGreen, LOW);
      digitalWrite(playerTwoRed, LOW);
      digitalWrite(playerOneRed, LOW);
      digitalWrite(playerTwoGreen, LOW);
    }
    if (playerOneScore > playerTwoScore) {
      digitalWrite(playerOneGreen, HIGH);
      digitalWrite(playerTwoRed, HIGH);
      Serial.println("GAME OVER!\nThe winner is Player 1!");
    }
    if (playerTwoScore > playerOneScore) {
      digitalWrite(playerTwoGreen, HIGH);
      digitalWrite(playerOneRed, HIGH);
      Serial.println("GAME OVER!\nThe winner is Player 2!");
    }
  }
}
