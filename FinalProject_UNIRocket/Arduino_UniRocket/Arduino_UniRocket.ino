const int adcPin = 1;
const int boostPin = 4;
const int pausePin = 42;

int boostTouchThreshold = 50000;

bool boostState = 0;
bool pauseState = 0;

int adcRead = 0;
int inByte = 0;

void setup() {
  pinMode(pausePin, INPUT_PULLUP);
  analogReadResolution(10);
  Serial.begin(9600);
}

bool touchGate(int tVal, int tThresh) {
  if (tVal > tThresh)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void loop() {
      adcRead = analogRead(adcPin);

      int boostVal = touchRead(boostPin);
      touchGate(boostVal, BoostTouchThreshold);
      boostState = touchGate(boostPin,boostTouchThreshold);

      int pauseVal = touchRead(pausePin);
      pauseState = !digitalRead(pausePin);
      Serial.print(adcRead);
      Serial.print(',');
      Serial.print(boostState);
      Serial.print(',');
      Serial.print(pauseState);
      Serial.print('\n');
  if(Serial.available())
  {
    inByte = Serial.read();
    if(inByte == 'A')
    {
      
    }
    else
    {
      Serial.println("Rx not working with me ToT");
    }
  }

}
