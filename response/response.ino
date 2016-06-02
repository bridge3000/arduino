#include <stdio.h>
#include <string.h>
#include <DS1302.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>     //包含头文件
LiquidCrystal_I2C lcd(0x27, 16, 2);  //创建一个对象：lcd

#include <ld3320.h>

VoiceRecognition Voice;                         //声明一个语音识别对象

#define Led 8                                   //定义LED控制引脚

#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.milan100.com";    // name address for Google (using DNS)
IPAddress ip(192, 168, 0, 120);
EthernetClient client;

int soundId;
String questionType = "";
String responseMsg = "";
int responseType = 0; //0正接收head_key, 1正接收head_value
String headKey = "";
String headValue = "";

/* 接口定义
CE(DS1302 pin5) -> Arduino D5
IO(DS1302 pin6) -> Arduino D6
SCLK(DS1302 pin7) -> Arduino D7
*/
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

/* 日期变量缓存 */
char date[50];
char time[50];
char day[10];

int numdata[7] = {0}, j = 0, mark = 0;
/* 创建 DS1302 对象 */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void setup()
{
  Serial.begin(9600);

  //ds1302
  rtc.write_protect(false);
  rtc.halt(false);

  //1602
  lcd.init();         //lcd初始化函数
  lcd.backlight();        //lcd开启背光灯函数
  lcd.begin(16, 2);

  //ld3320
  Voice.init();                               //初始化VoiceRecognition模块
  Voice.addCommand("kai deng", 0);            //添加指令，参数（指令内容，指令标签（可重复））
  Voice.addCommand("guan deng", 1);           //添加指令，参数（指令内容，指令标签（可重复））
  Voice.addCommand("ri qi", 2);              //添加垃圾词汇
  Voice.addCommand("shi jian", 2);              //添加垃圾词汇
  Voice.addCommand("tian qi", 3);
  Voice.start();//开始识别

  //w5100
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  // give the Ethernet shield a second to initialize:
  Serial.println("initialize network...");
  delay(1000);
}

void loop()
{
  recogniseSound();

  receiveResponse();
}

void recogniseSound()
{
  //ld3320 recoginze
  soundId = Voice.read();
  if (soundId != -1)
  {
    Serial.println(soundId);
  }

  switch (soundId)                         //判断识别
  {
    case 0:
      kaideng();
      break;
    case 1:
      guandeng();
      break;
    case 11:
      getServerTime();
      break;
    default:
      hello();
  }
}

void receiveResponse()
{
  //http response
  if (client.available()) {
    char c = client.read();
    //    Serial.print(c);

    if (responseType == 0)
    {
      if (c != ':')
      {
        headKey += c;
      }
      else
      {
        responseType = 1;
      }
    }
    else if (responseType == 1)
    {
      if (c != '\r\n')
      {
        headValue += c;
      }
      else
      {
        responseType = 0;
        if(headKey == "Question-Type")
        {
          questionType = headValue;  
        }
        else if(headKey == "Response-Msg")
        {
          responseMsg = headValue;
        }
      }
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println("disconnecting.");
    client.stop();

    //split the response string, \r\n
    lcd.clear();
    lcd.print(responseMsg);

    responseType = 0;
    questionType = "";
    responseMsg = "";
  }
}

void sendServerQuestion(String action)
{
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /response/" + action + " HTTP/1.1");
    client.println("Host: www.milan100.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }
}

void getServerTime()
{
  sendServerQuestion("show_time");
}

/* 从 DS1302 获取当前时间 */
void print_time()
{
  Time t = rtc.time();
  /* 将星期从数字转换为名称 */
  memset(day, 0, sizeof(day));
  switch (t.day)
  {
    case 1: strcpy(day, "Sun"); break;
    case 2: strcpy(day, "Mon"); break;
    case 3: strcpy(day, "Tue"); break;
    case 4: strcpy(day, "Wed"); break;
    case 5: strcpy(day, "Thu"); break;
    case 6: strcpy(day, "Fri"); break;
    case 7: strcpy(day, "Sat"); break;
  }

  /* 将日期代码格式化凑成buf等待输出 */
  //  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);
  snprintf(date, sizeof(date), "%s %04d-%02d-%02d", day, t.yr, t.mon, t.date);
  snprintf(time, sizeof(time), "%02d:%02d:%02d", t.hr, t.min, t.sec);

  lcd.print(date);
  lcd.setCursor(0, 1);
  lcd.print(time);
  delay(1000);         //延时1s
  lcd.clear();         //清空lcd显示
}

void kaideng()
{
  //	digitalWrite(Led,HIGH);                 //点亮LED
  lcd.print("kaideng");
  delay(1000);         //延时1s
  lcd.clear();         //清空lcd显示
}

void guandeng()
{
  //	digitalWrite(Led,LOW);//熄灭LED
  lcd.print("guandeng");
  delay(1000);         //延时1s
  lcd.clear();         //清空lcd显示
}

void hello()
{
  lcd.print("hello");
  delay(1000);         //延时1s
  lcd.clear();         //清空lcd显示
}


