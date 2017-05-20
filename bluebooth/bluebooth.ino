#define AT 2
#define LED 13
void setup()
{
       pinMode(LED,OUTPUT);
       pinMode(AT,OUTPUT);
       digitalWrite(AT,HIGH);
       Serial.begin(9600);//这里应该和你的模块通信波特率一致
       delay(100);
       Serial.println("AT");
       delay(100);
       Serial.println("AT+NAME=OPENJUMPER-Bluetooth");//命名模块名
       delay(100);
       Serial.println("AT+ROLE=0");//设置主从模式：0从机，1主机
       delay(100);
       Serial.println("AT+PSWD=1234");//设置配对密码，如1234
       delay(100);
       Serial.println("AT+UART=4800,0,0");//设置波特率9600，停止位1，校验位无
       delay(100);
       Serial.println("AT+RMAAD");//清空配对列表
}
void loop()
{
       digitalWrite(LED, HIGH);
       delay(500);
       digitalWrite(LED, LOW);
       delay(500);
}
