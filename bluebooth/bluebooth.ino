void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available())
  {
    char c = Serial.read();
    Serial.println(c);
    if (c == 'A')
    {
      Serial.println("Hello I am amarino");
    }
  }
}
