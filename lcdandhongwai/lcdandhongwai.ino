#include <IRremote.h>//包含红外库
#include <Wire.h>
#include <LiquidCrystal_I2C.h>     //包含头文件
LiquidCrystal_I2C lcd(0x27, 16, 2);  //创建一个对象：lcd

int RECV_PIN = 13;//端口声明

IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明
// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN)
  {
    Serial.println("Could not decode message");
  }
  else
  {
    if (results->decode_type == NEC)
    {
      Serial.print("Decoded NEC: ");
    }
    else if (results->decode_type == SONY)
    {
      Serial.print("Decoded SONY: ");
    }
    else if (results->decode_type == RC5)
    {
      Serial.print("Decoded RC5: ");
    }
    else if (results->decode_type == RC6)
    {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++)
  {
    if ((i % 2) == 1)
    {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else
    {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}

void setup()
{
  pinMode(RECV_PIN, INPUT);   //端口模式，输入

  Serial.begin(9600);	//波特率9600
  irrecv.enableIRIn(); // Start the receiver

  lcd.init();         //lcd初始化函数
  lcd.backlight();        //lcd开启背光灯函数

}

int on = 0;
unsigned long last = millis();

void loop()
{
  lcd.clear();

  if (irrecv.decode(&results)) //调用库函数：解码
  {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250)
    {
      dump(&results);

      lcd.print(results.value);
      delay(2000);

    }

    last = millis();
    irrecv.resume(); // Receive the next value
  }
}

