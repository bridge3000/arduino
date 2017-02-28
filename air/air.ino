void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {

  delay(2000);
 int voltage = analogRead(A0);

  Serial.println(voltage);
}
