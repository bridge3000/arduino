//数字端口定义
int ledPin = 7;
int Left_motor_back = 8;   //左电机后退(IN1)
int Left_motor_go = 9;   //左电机前进(IN2)
int Right_motor_go = 10;  // 右电机前进(IN3)
int Right_motor_back = 11;  // 右电机后退(IN4)

//变量
int speed = 80;
int acceleration = 20; //加速度
int turnSpeed = 80;
bool isLighting = false;
char cmdGo  = 'f';
char cmdBrake = 'b';
char cmdLeft = 'l';
char cmdRight = 'r';
char cmdForceBrake = 's';
char cmdLight = 'i';

void setup()
{
  Serial.begin(9600);//设置波特率为9600

  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go, OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT); // PIN 10 (PWM)
  pinMode(Right_motor_back, OUTPUT); // PIN 11 (PWM)
  
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  char c = Serial.read();  
//  Serial.println(c);
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
  Serial.println("#") ;
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
  Serial.println("#") ;
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

void forceBrake()
{
  Serial.println("force brake#") ;
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
}

//左转(左轮不动，右轮前进)
void left()
{
  Serial.println("left#") ;
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
  Serial.println("right#") ;
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

void light()
{
  Serial.println("light#") ;
  if(isLighting)
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

