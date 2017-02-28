#include <SPI.h>
#include <Ethernet.h>
#include <Syn6288.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.milan100.com";    // name address for Google (using DNS)
IPAddress ip(192, 168, 0, 120);
EthernetClient client;

String questionType = "";
String responseMsg = "";
int responseType = 0; //0正接收head_key, 1正接收head_value
String headKey = "";
String headValue = "";

Syn6288 syn;
uint8_t text1[20]; 
int iii = 0; //中文字符的码的长度
int isFetching = 0; //是否正在获取信息

void setup()
{
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  Serial.println("initialize network...");
  delay(1000);  
}

void loop()
{   
  if(isFetching)
  {
    receiveResponse();
  }
  else 
  {
    getSoundText();
  }  
}

/*每次接收一个字符*/
void receiveResponse() 
{
  if (client.available()) 
  {
    char c = client.read();

    if (responseType == 0)
    {
      if (c != ':') //正在接收key
      {
        headKey += c;
      }
      else //key接收完毕
      {
        responseType = 1;
      }
    }
    else if (responseType == 1)
    {
      if (c != '\n') //正在接收value
      {
        if (c != 32) //:后面的空格不处理
        {
          headValue += c;
          if (headKey == "Response-Msg")
          {
            text1[iii] = c;
            iii++;
          }
        }
      }
      else //换行了，开始读value
      {
        responseType = 0;
        if (headKey == "Question-Type")
        {
          questionType = headValue;
        }
        else if (headKey == "Response-Msg")
        {
          responseMsg = headValue;
        }

        headKey = "";
        headValue = "";
      }
    }
  }

  if (!client.connected()) //连接结束，把变量都初始化
  {
    client.stop();

    responseType = 0;
    questionType = "";

    syn.play(text1, iii, 3);    
    iii = 0;
    isFetching = 0;
    for(int i=0;i<20;i++)
    {
      text1[i] = 0;
    }
  
    delay(10000);
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
    isFetching = 1;
  }
  else {
    Serial.println("connection failed");
  }
}

void getSoundText()
{
  sendServerQuestion("get_audio");
  isFetching = 1;
}

