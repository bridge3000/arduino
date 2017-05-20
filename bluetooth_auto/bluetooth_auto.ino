#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7);  // RX, TX

#include "Syn6288.h"
Syn6288 syn;

//数字端口定义
int ledPin = 5;

int Left_motor_go = 10;   //左电机前进(IN2)
int Left_motor_back = 11;   //左电机后退(IN1)
int Right_motor_go = 9;  // 右电机前进(IN3)
int Right_motor_back = 8;  // 右电机后退(IN4)

int angelAdding = 20; //转向增加的度

//变量
int leftSpeed = 0;
int rightSpeed = 0;
int initSpeed = 70; //初始速度
int reverseSpeed = 70;
int acceleration = 20; //加速度
int turnSpeed = 80;
bool isLighting = false;
char cmdGo  = 'f';
char cmdBrake = 'b';
char cmdLeft = 'l';
char cmdRight = 'r';
char cmdForceBrake = 's';
char cmdLight = 'i';
char cmdReverse = 'e';

void initBothSpeed()
{
  leftSpeed = initSpeed;
  rightSpeed = initSpeed + 20;
}

void setup()
{
  Serial.begin(9600);//设置波特率为9600

  mySerial.begin(9600);

  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  pinMode(ledPin, OUTPUT);

  initBothSpeed();

  //  uint8_t text1[] = {0xCE,0xD2,0xCA,0xC7,0xD6,0xD0,0xB9,0xFA,0xC8, 0xCB}; //我是中国人
  uint8_t text1[] = {0xB3, 0xB5, 0xC1, 0xBE, 0xD2, 0xD1, 0xC6, 0xF4, 0xB6, 0xAF}; //车辆已启动
  syn.play(text1, sizeof(text1), 0);

}


void loop()
{
  //  if (mySerial.available())
  //    Serial.write(mySerial.read());

  //  char c = Serial.read();
  char c = mySerial.read();
  if (c == cmdGo)
  {
    go();
  }
  else if (c == cmdBrake)
  {
    brake();
  }
  else if (c == cmdLeft)
  {
    left();
  }
  else if (c == cmdRight)
  {
    right();
  }
  else if (c == cmdForceBrake)
  {
    forceBrake();
  }
  else if (c == cmdLight)
  {
    light();
  }
  else if (c == cmdReverse)
  {
    back();
  }

}

void go()     // 前进
{
  leftSpeed += acceleration;
  rightSpeed += acceleration;
  if (leftSpeed > 255)
  {
    leftSpeed = 255;
  }

  if (rightSpeed > 255)
  {
    rightSpeed = 255;
  }

  digitalWrite(Right_motor_go, HIGH); // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, rightSpeed); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back, 0);
  digitalWrite(Left_motor_go, HIGH); // 左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, leftSpeed); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back, 0);

  uint8_t text1[] = {0xBC, 0xD3, 0xCB, 0xD9}; //加速
  syn.play(text1, sizeof(text1), 0);
}

//刹车，减速
void brake()
{


  leftSpeed -= acceleration;
  rightSpeed -= acceleration;
  if (leftSpeed < 0)
  {
    leftSpeed = 0;
  }

  if (rightSpeed < 0)
  {
    rightSpeed = 0;
  }

  if (leftSpeed > 0 && rightSpeed > 0)
  {
    digitalWrite(Right_motor_go, HIGH); // 右电机前进
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, rightSpeed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Right_motor_back, 0);
    digitalWrite(Left_motor_go, HIGH); // 左电机前进
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, leftSpeed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Left_motor_back, 0);
  }
  else
  {
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
  }

  uint8_t text1[] = {0xC9, 0xB2, 0xB3, 0xB5}; //刹车
  syn.play(text1, sizeof(text1), 0);

}

//强行刹车
void forceBrake()
{
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  initBothSpeed();

  uint8_t text1[] = {0xC7, 0xBF, 0xD6, 0xC6, 0xC9, 0xB2, 0xB3, 0xB5};
  syn.play(text1, sizeof(text1), 0);
}

//左转
void left()
{
  leftSpeed -= angelAdding;

  digitalWrite(Left_motor_go, HIGH); //左电机前进
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, leftSpeed);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速

  uint8_t text1[] = {0xD7, 0xF3, 0xD7, 0xAA};
  syn.play(text1, sizeof(text1), 0);
}

//右转(右轮不动，左轮前进)
void right()
{
  rightSpeed -= angelAdding;
  digitalWrite(Right_motor_go, HIGH);	// 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, rightSpeed);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速

  uint8_t text1[] = {0xD3, 0xD2, 0xD7, 0xAA};
  syn.play(text1, sizeof(text1), 0);
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

void back()          //倒车
{
  digitalWrite(Right_motor_go, LOW); //右轮后退
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, reverseSpeed); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW); //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, reverseSpeed); //PWM比例0~255调速
  initBothSpeed();

  uint8_t text1[] = {0xB5, 0xB9, 0xB3, 0xB5};
  syn.play(text1, sizeof(text1), 0);
}

//灯光
void light()
{
  Serial.println("light#") ;
  if (isLighting)
  {
    digitalWrite(ledPin, LOW);
    isLighting = false;
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    isLighting = true;
  }

}

