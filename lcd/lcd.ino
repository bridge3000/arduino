#include <Wire.h> 
#include <LiquidCrystal_I2C.h>     //包含头文件
LiquidCrystal_I2C lcd(0x27,16,2);    //创建一个对象：lcd
/******************************************/
void CollectDate()        //采集电压值函数
{
  char i;
  double voldate=0;
  long orldate=0,sumdate=0;
  for(i=0;i<10;i++)        //将采集到的10次电压值相加求和
  {
    sumdate=sumdate+analogRead(A0);
  }
  
  orldate=sumdate/10;       //求出平均值
  voldate=orldate*5.0/1023;      //将电压值由数字量换成模拟量
  lcd.print(voldate);       //lcd显示模拟电压值
  lcd.print("V");
}
/******************************************/
void setup()
{
  lcd.init();         //lcd初始化函数
  lcd.backlight();        //lcd开启背光灯函数
  lcd.print("success");
  delay(5000);
}
/******************************************/
void loop()
{
   CollectDate();        //采集数据
   delay(1000);         //延时1s
   lcd.clear();         //清空lcd显示
}
