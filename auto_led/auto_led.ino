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
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }

//  Serial.print("light=");
//  Serial.println(lightState);

  delay(100);
}
