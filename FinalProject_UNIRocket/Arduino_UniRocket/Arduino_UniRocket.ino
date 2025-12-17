const int adcPin = 1;
const int boostPin = 4;

int boostTouchThreshold = 50000;

bool boostState = 0;
bool dummy1 = 0;
bool dummy2 = 0;

int adcRead = 0;
int inByte = 0;

void setup() {
  analogReadResolution(10);
  Serial.begin(9600);
}

void loop() {
  adcRead = analogRead(adcPin);

      int boostVal = touchRead(boostPin);
      if(boostVal > boostTouchThreshold)
      {
        boostState = true;
      }
      else {
        boostState = false;
      }
      
      Serial.print(adcRead);
      Serial.print(',');
      Serial.print(boostState);
      Serial.print(',');
      Serial.print(dummy1);
      Serial.print(',');
      Serial.print(dummy2);
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
