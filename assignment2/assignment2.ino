const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;
const int ledPin4 = 7;
const int ledTool = 38;

const int potPin = 15;

const int buttonPin = 9;

bool buttonState = 0;
bool lastButtonState = 0;
bool toggle = 0;
bool fallToggle = 0;


void setup() {
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);

  analogReadResolution(10);
  pinMode(potPin,INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  int adcVal = analogRead(potPin);
  int simplify = map(adcVal, 0, 1023, 0, 255);
  buttonState = !digitalRead(buttonPin);

  if (toggle){
    analogWrite(ledPin1,simplify);
    analogWrite(ledPin2,simplify);
    analogWrite(ledPin3,simplify);
    analogWrite(ledPin4,simplify);
  }

  if (!toggle){
    analogWrite(ledPin1,0);
    analogWrite(ledPin2,0);
    analogWrite(ledPin3,0);
    analogWrite(ledPin4,0);
  }

  if (buttonState && !lastButtonState){
    toggle = !toggle;
  }

  if (!buttonState && lastButtonState){
    fallToggle = !fallToggle;
  }

  lastButtonState = buttonState;

  Serial.println(simplify);
}
