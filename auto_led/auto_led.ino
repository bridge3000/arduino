int infraredPin = 2;
int ledPin = 13;
int lightPin = 7;

void setup() {
  pinMode(infraredPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(lightPin, INPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
}
void loop() {
  int infraredPinState = digitalRead(infraredPin);
  int lightState = digitalRead(lightPin);
  //  Serial.println(infraredPinState);

  if ( (infraredPinState == 1) && (lightState == 1))
  {
    delay(2000);
    if ( (infraredPinState == 1) && (lightState == 1)) //2秒后还能检测到生物红外说明不是临时通过
    {
      digitalWrite(ledPin, HIGH);
      delay(30000);
      digitalWrite(ledPin, LOW);
    }
  }

  //  Serial.print("light=");
  //  Serial.println(lightState);

  delay(100);
}
