#include <IRremote.h>
 
int RECV_PIN = 11;//定义红外接收器的引脚为11
int LED1 = 10;
long on  = 0x00FF6897;//编码示例,与发送匹配用
long off = 0x00ff30CF;
int isOn = 0;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 初始化红外接收器
  pinMode(LED1, OUTPUT);//端口模式，输出
}
 
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);//以16进制换行输出接收代码
    Serial.println();//为了便于观看输出结果增加一个空行
    
    if (results.value == on )
    {
      isOn = 1;
    }
    else if (results.value == off )
    {
      isOn = 0;
    }       
       
   if (isOn)
   {
     digitalWrite(LED1, HIGH);
   }
   else
   {
     digitalWrite(LED1, LOW); 
   }
 
       
    irrecv.resume(); // 接收下一个值
  }
}
