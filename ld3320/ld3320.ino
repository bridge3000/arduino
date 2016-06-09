#include <ld3320.h>

VoiceRecognition Voice;                         //声明一个语音识别对象

#define Led 8                                   //定义LED控制引脚

int soundId;

void setup() 
{

  
  
//    pinMode(Led,OUTPUT);                        //初始化LED引脚为输出模式
//    digitalWrite(Led,LOW);                      //LED引脚低电平
    Serial.begin(9600);                        //配置9600

  Serial.println(MOSI);
  Serial.println(MISO);
  Serial.println(SCK);
  
    Serial.print("Uart start!");                
    Voice.init();         
    Voice.micVol(60);
    
    
    //初始化VoiceRecognition模块   
    Voice.addCommand("kai deng",0);             //添加指令，参数（指令内容，指令标签（可重复））
    Voice.addCommand("guan deng",1);            //添加指令，参数（指令内容，指令标签（可重复））
    Voice.addCommand("ni hao",2);               //添加垃圾词汇
    Voice.addCommand("zai jian",3);              //添加垃圾词汇
    Voice.start();//开始识别
}
void loop() {
  soundId = Voice.read();
  
  if(soundId != -1)
  {
    Serial.println(soundId);
  }
  
  switch(soundId)                          //判断识别
  {
    case 0:                                     //若是指令“kai deng”
//	digitalWrite(Led,HIGH);                 //点亮LED
        Serial.println("LED ON");
        break;
    case 1:                                     //若是指令“guan deng”
//	digitalWrite(Led,LOW);//熄灭LED
        Serial.println("LED OFF");
        break;   
    case 2:
        Serial.println("ni hao");
        break;   
    case 3:
        Serial.println("wei wei");
        break;   
    default:
        break;
  }
}
