int infraredPin = 2; //红外传感器
int ledPin = 13; //目前使用继电器 如果使用数字口的话也可以
int lightPin = 7; //光强传感器
int relayPin = 8; //继电器
unsigned long  lastTime = 0;
int ledStatus = 0;

void setup() {
  pinMode(infraredPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(lightPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  int infraredPinState = digitalRead(infraredPin);
  int lightState = digitalRead(lightPin);
  Serial.println(infraredPinState);
  
  unsigned long curTime = millis();

  if ( infraredPinState == 1)
  {
    lastTime = curTime;
    
    if(ledStatus == 0)
    {
      digitalWrite(relayPin, LOW);
      ledStatus = 1;
    }   
  }
  else if ( infraredPinState == 0)
  {
    if ( (curTime - lastTime) > 30000)
    {
      digitalWrite(relayPin, HIGH);
      ledStatus = 0;
    }
  }
  
  delay(100);
}
