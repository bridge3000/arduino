#include "Syn6288.h"

Syn6288 syn;
char str1[] = {"我是中国人"};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  syn.Speech(str1); //语音3,出门请带上手机钥匙钱包;
}
