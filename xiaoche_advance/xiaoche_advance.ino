//============================亚博科技===========================
//  智能小车前后左右综合实验
//===============================================================
//#include <Servo.h>
#include <IRremote.h>//包含红外库
int RECV_PIN = 13;//端口声明

IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明
int Left_motor_back = 8;   //左电机后退(IN1)
int Left_motor_go = 9;   //左电机前进(IN2)

int Right_motor_go = 10;  // 右电机前进(IN3)
int Right_motor_back = 11;  // 右电机后退(IN4)
int val;
int speed = 100;
int acceleration = 20; //加速度
int turnSpeed = 100;
unsigned long last = millis();
long cmdGo1  = 0x80102658;//编码示例,与发送匹配用
long cmdGo2  = 0x8010A658;
long cmdBrake1 = 0x8010A659;
long cmdBrake2 = 0x80102659;


long cmdLeft1 = 0x8010A65A;
long cmdLeft2 = 0x8010265A;
long cmdRight1 = 0x8010265B;
long cmdRight2 = 0x8010A65B;

void setup()
{
  Serial.begin(9600);//设置波特率为9600
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("start..." ) ;

  pinMode(RECV_PIN, INPUT);   //端口模式，输入
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go, OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT); // PIN 10 (PWM)
  pinMode(Right_motor_back, OUTPUT); // PIN 11 (PWM)
}

void loop()
{
  //  val = Serial.read();//读取串口收到的数据
  if (irrecv.decode(&results)) //调用库函数：解码
  {
    if (millis() - last > 250)
    {
      dump(&results);

      if (results.value == cmdGo1 || results.value == cmdGo2)
      {
        go();
      }
      else if (results.value == cmdBrake1 || results.value == cmdBrake2)
      {
        brake();
      }
      else if (results.value == cmdLeft1 || results.value == cmdLeft2)
      {
        left();
      }
      else if (results.value == cmdRight1 || results.value == cmdRight2)
      {
        right();
      }
    }


    last = millis();
    irrecv.resume(); // Receive the next value
  }

}

void go()     // 前进
{
  speed += acceleration;
  if (speed > 255)
  {
    speed = 255;
  }

  Serial.println("go, speed=") ;
  Serial.println(speed) ;
  digitalWrite(Right_motor_go, HIGH); // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back, 0);
  digitalWrite(Left_motor_go, HIGH); // 左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back, 0);
}

//刹车，停车
void brake()
{
  Serial.println("brake, speed=") ;
  Serial.println(speed) ;
  speed -= acceleration;
  if (speed < 0)
  {
    speed = 0;
  }

  if (speed > 0)
  {
    digitalWrite(Right_motor_go, HIGH); // 右电机前进
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Right_motor_back, 0);
    digitalWrite(Left_motor_go, HIGH); // 左电机前进
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Left_motor_back, 0);
  }
  else
  {
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
  }

}

//左转(左轮不动，右轮前进)
void left()
{
  Serial.println("left") ;
  digitalWrite(Right_motor_go, HIGH);	// 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, turnSpeed);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮不动
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速
}

//右转(右轮不动，左轮前进)
void right()
{
  Serial.println("right") ;
  digitalWrite(Right_motor_go, LOW);  //右电机不动
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, turnSpeed);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速
}

//急左转(左轮后退，右轮前进)
void spin_left(int time)
{
  digitalWrite(Right_motor_go, HIGH);	// 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 200);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 200); //PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整
}

//急右转(右轮后退，左轮前进)
void spin_right(int time)
{
  digitalWrite(Right_motor_go, LOW);  //右电机后退
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 200); //PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 200);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整
}

void back(int time)          //倒车
{
  digitalWrite(Right_motor_go, LOW); //右轮后退
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 150); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW); //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 150); //PWM比例0~255调速
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

