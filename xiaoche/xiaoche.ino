//============================亚博科技===========================
//  智能小车前进实验
//===============================================================
//#include <Servo.h> 
#include <IRremote.h>//包含红外库
int RECV_PIN = 13;//端口声明

IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明

long on1  = 0x8010A610;//编码示例,与发送匹配用
long off1 = 0x80102611;

int Left_motor_back=8;     //左电机后退(IN1)
int Left_motor_go=9;     //左电机前进(IN2)

int Right_motor_go=10;    // 右电机前进(IN3)
int Right_motor_back=11;    // 右电机后退(IN4)

int on = 0;
unsigned long last = millis();

void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  
	pinMode(RECV_PIN, INPUT);   //端口模式，输入

	Serial.begin(9600);	//波特率9600
	irrecv.enableIRIn(); // Start the receiver

}
void run(int time)     // 前进
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
//  analogWrite(Right_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
//  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);
//  analogWrite(Left_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
//  analogWrite(Left_motor_back,0);
//  delay(time * 100);   //执行时间，可以调整  
}

void cheon()     // 前进
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);
}

void cheoff()     // 前进
{
  digitalWrite(Right_motor_go,LOW);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     

  digitalWrite(Left_motor_go,LOW);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);

}

void loop()
{
//  delay(500);
//  run(10); 	//前进
  
    if (irrecv.decode(&results)) //调用库函数：解码
   {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) 
      {
       on = !on;
       digitalWrite(13, on ? HIGH : LOW);
       dump(&results);
      }
    if (results.value == on1 )
    {
      Serial.print("on");
       cheon();
    }
    if (results.value == off1 )
     {
       Serial.print("off");
     cheoff();  
   }
    
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}

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

