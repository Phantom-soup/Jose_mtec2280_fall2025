const int ledRedRight = 4;
const int ledBlueRight = 5;
const int ledGoal = 6;
const int ledRedLeft = 7;
const int ledBlueLeft = 1;
const int ledTool = 38;

const int buttonGuess = 9;
bool guessButtonState = 0;
bool lastGuessState = 0;
int lastGuessTime = 0;
int debounceGuess = 25;
bool doubleGuess = 1;

const int buttonHint = 10;
bool hintButtonState = 0;
bool lastHintState = 0;
int lastHintTime = 0;
int debounceHintTime = 20;
bool doubleHint = 0;

const int potPin = 15;
int goalValue = 0;
int insertValue = 0;
int previousValue = 0;
int HintValue = 0;

bool goalReached = 0;
bool redBuster = 0;
bool hintAsked = 0;

int currentTime = 1;
int test = 0;

void setup() {
  pinMode(ledRedRight,OUTPUT);
  pinMode(ledBlueRight,OUTPUT);
  pinMode(ledGoal,OUTPUT);
  pinMode(ledRedLeft,OUTPUT);
  pinMode(ledBlueLeft,OUTPUT);
  pinMode(buttonGuess,INPUT_PULLUP);
  pinMode(buttonHint,INPUT_PULLUP);

  analogReadResolution(10);
  pinMode(potPin,INPUT_PULLUP);

  goalValue = random(10, 220);
  int adcVal = analogRead(potPin);
  int simplify = map(adcVal, 0, 1023, 0, 255);
  insertValue = simplify;
  previousValue = insertValue;
  Serial.begin(115200);
}

void loop() {
  int adcVal = analogRead(potPin);
  int currentValue = map(adcVal, 0, 1023, 0, 255);
  currentTime = millis();
  bool b1 = !digitalRead(buttonGuess);
  bool b2 = !digitalRead(buttonHint);

  if (b1 != lastGuessState) {
    lastGuessTime = millis();
  }
  if (b2 != lastHintState) {
    lastHintTime = millis();
  }

  if ((currentTime - lastGuessTime) > debounceGuess) {
    if (b1 != guessButtonState) {
      guessButtonState = b1;
    }
  }
  if ((currentTime - lastHintTime) > debounceHintTime) {
    if (b2 != hintButtonState) {
      hintButtonState = b2;
    }
  }

  if (guessButtonState == HIGH && hintButtonState == HIGH) {
    goalValue = random(10, 220);
    previousValue = insertValue;
    hintAsked = 0;
    goalReached = 0;
  }
  else if (guessButtonState == HIGH && guessButtonState == doubleGuess) {
    previousValue = insertValue;
    insertValue = currentValue;

    int insertCheck = insertValue - goalValue;
    int previousCheck = previousValue - goalValue;

    if (abs(insertCheck) < abs(previousCheck)){
      redBuster = 1;
    }
    else {
      redBuster = 0;
    }

    if (goalReached == HIGH) {
      goalValue = random(10, 255);
    }

    if (insertValue > (goalValue - 10) && insertValue < (goalValue + 10) ) {
      goalReached = 1;
      redBuster = 1;
    }
    else{
      goalReached = 0;
    }

    hintAsked = 0;
    doubleGuess = 0;
  }
  else if (hintButtonState == HIGH && hintButtonState == doubleHint) {
    hintAsked = 1;

    doubleHint = 0;
  }

  int closeness = 2*(goalValue - insertValue);
  int blueLightSpecial = constrain(255 - abs(closeness), 0, 255);

  digitalWrite(ledRedRight,redBuster);
  analogWrite(ledBlueRight,blueLightSpecial);
  digitalWrite(ledGoal,goalReached);
  digitalWrite(ledRedLeft,redBuster);
  analogWrite(ledBlueLeft,blueLightSpecial);

  if (hintAsked == HIGH) {
    if (insertValue < (goalValue - 10)){
      analogWrite(ledBlueLeft, 0);
      digitalWrite(ledRedLeft, LOW);
    }
    if (insertValue > (goalValue + 10)){
      digitalWrite(ledRedRight, LOW);
      analogWrite(ledBlueRight, 0);
    }
  }

  if (guessButtonState == LOW) {
    doubleGuess = 1;
  }
  if (hintButtonState == LOW) {
    doubleHint = 1;
  }
  lastGuessState = b1;
  lastHintState = b2;

  //Serial.println(test);
  //Serial.printf("Guess = %i | dGuess = %i | Hint = %i | dHint = %i \n",guessButtonState, doubleGuess, hintButtonState, doubleHint);
  //Serial.printf("Hint = %i | Red = %i | Goal = %i \n", hintAsked, redBuster, goalReached);
  Serial.printf("G = %i | C = %i | I = %i | P = %i | B = %i \n", goalValue, currentValue, insertValue, previousValue, blueLightSpecial);
}
