int buzzer=8;//设置控制蜂鸣器的数字IO脚
int receive = 9;
int i = 0;
int toggle = 0;

void setup() 
{ 
  pinMode(buzzer, OUTPUT);//设置数字IO脚模式，OUTPUT为输出 
  pinMode(receive, INPUT);
} 
void loop() 
{ 
  Serial.println(digitalRead(receive));
  if(digitalRead(receive) == HIGH)
  {
    if(toggle == 1)
    {
      toggle = 0;
    }
    else
    {
      toggle = 1;
    }    
  }

  Serial.println(toggle);

  if(toggle == 1)
  {
    for(i=0;i<80;i++)//输出一个频率的声音
//    for(i=0;i<10;i++)//输出一个频率的声音
    { 
      digitalWrite(buzzer,HIGH);//发声音
      delay(1);//延时1ms 
      digitalWrite(buzzer,LOW);//不发声音
      delay(1);//延时ms 
    } 

    for(i=0;i<100;i++)//输出另一个频率的声音 
//    for(i=0;i<20;i++)//输出另一个频率的声音 
    { 
      digitalWrite(buzzer,HIGH);//发声音
      delay(2);//延时2ms 
      digitalWrite(buzzer,LOW);//不发声音
      delay(2);//延时2ms 
    } 
  }


  

}
