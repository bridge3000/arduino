/*
[url=http://www.openjumper.com/]www.openjumper.com[/url]
日期:2013.5.18
IDE 版本:1.0.1
功能：模拟声控灯开关状态，当音量超过设定值后，点亮LED，延时一段时间后熄灭
*/
int LEDpin = 13;                 //定义LED灯控制引脚

void setup() {
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  int Soundvalue = analogRead(A0);  //读取输入模拟值
  if (Soundvalue > 20)
  {
    digitalWrite(LEDpin, HIGH);     //当模拟值大于设定值后，点亮LED
    for (int i = 0; i < 20; i++) {
      delay(1000);                    //延时20s
    }
  }
  else {
    digitalWrite(LEDpin, LOW);     //关闭LED
  }
}
