#include "Syn6288.h"
Syn6288 syn;
 
//uint8_t text1[] = {0xCE,0xD2,0xCA,0xC7,0xD6,0xD0,0xB9,0xFA,0xC8, 0xCB}; //我是中国人
//uint8_t text1[] = {0xCE,0xD2,0xCA,0xC7, 0xc7,0xc7,0xc7,0xc7}; //我是乔乔
uint8_t text1[] = {0xbb,0xb6,0xd3,0xad,0xb9,0xe2,0xc1,0xd9}; //欢迎光临
int infraredPin = 2; //红外传感器

void setup()
{
  Serial.begin(9600);
  pinMode(infraredPin, INPUT);
}

void loop()
{
  int infraredPinState = digitalRead(infraredPin);
  if ( infraredPinState == 1)
  {
    syn.play(text1, sizeof(text1), 1);
    delay(10000);   //循环间隔100uS
  }    
}
 
