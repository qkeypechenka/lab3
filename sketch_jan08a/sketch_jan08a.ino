const int buzzerPin = 9;
const int led1Pin = 1;
const int led2Pin = 2;
const int button1Pin = 3;
const int button2Pin = 4;

bool isStarted = false;
bool isWaiting = false;

int timer = 0;
long currentTime = 0;


void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  digitalWrite(button1Pin, 1);
  pinMode(button2Pin, INPUT_PULLUP);
  digitalWrite(button2Pin, 1);
  pinMode(buzzerPin, OUTPUT);
}


void loop() {
  if (isStarted) {
    if (currentTime + timer > millis()) {
       checkFalseStart();
    } else {
      checkWinner();
    }
  } else {
    if (playersReady()) {
         playStartSound();
         timer = random(500, 5000);
         currentTime = millis();
     } else if (currentTime + timer <= millis()) {
         isStarted = true;
         playSound();
    } 
  }
}


bool playersReady() {
  return digitalRead(button1Pin) == 0 && digitalRead(button2Pin) == 0;
}


void checkFalseStart() {
  if (digitalRead(button1Pin) == 0) {
    showLEDsignal(led2Pin);
    isStarted = false;
  } else if (digitalRead(button2Pin) == 0) {
    showLEDsignal(led1Pin);
    isStarted = false;
  }
}


void checkWinner() {
  if (digitalRead(button1Pin) == 0) {
    showLEDsignal(led1Pin);
    isStarted = false;
  } else if (digitalRead(button2Pin) == 0) {
    showLEDsignal(led2Pin);
    isStarted = false;
  }
}


void playSound() {
  tone(buzzerPin, 500, 300);
}


void showLEDsignal(int pin) {
  digitalWrite(pin, 1);
  delay(1000);
  digitalWrite(pin, 0);
}


void playStartSound() {
  tone(buzzerPin, 500, 300);
  digitalWrite(led1Pin, 1);
  digitalWrite(led2Pin, 1);
  delay(1000);
  digitalWrite(led1Pin, 0);
  digitalWrite(led2Pin, 0);
}
