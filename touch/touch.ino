int ledPin = 13; //定义数字10 接口
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, INPUT);//定义小灯接口为输出接口
}
void loop()
{
  int infraredPinState = digitalRead(ledPin);
  Serial.println(infraredPinState);
}

