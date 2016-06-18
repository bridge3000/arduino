#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "Syn6288.h"

Syn6288::Syn6288()
{
	_nPort = 1;
	_nBkm = 0;
}

void Syn6288::Speech(const char * txt,uchar bkm,uchar port)
{
	uchar i=0;
	uchar head[5];
	uchar x=0;

	head[0]=0xfd;
	head[1]=0x00;
	head[3]=0x01;

	_nPort=port;
	_nBkm=bkm % (BKM_MAX + 1);
	head[2]=sizeof(txt) + 3;
	head[4]=_nBkm << 3;
	Serial.write(head,HEAD_LEN);
	for(i=0;i<HEAD_LEN;i++)
	{
		x=x^head[i];
		if(_nPort==1)
			Serial.write(head[i]);
		else if(_nPort==2)
//			Serial2.write(head[i]); //可能是软串口，程序里没有体现，所以暂时注释
			Serial.write(head[i]);
	}

	for(i=0;i<head[2];i++)
	{
		x=x^txt[i];
		if(_nPort==1)
			Serial.write(txt[i]);
		else if(_nPort == 2)
//			Serial2.write(txt[i]);
			Serial.write(txt[i]);
	}
	
	if(_nPort == 1)
		Serial.write(x);
	else if(_nPort == 2)
//		Serial2.write(x);
		Serial.write(x);
}

void Syn6288::Speech(const char * txt,uchar bkm)
{
	Speech(txt,bkm,_nPort);
}

void Syn6288::Speech(const char * txt)
{
	Speech(txt,_nBkm,_nPort);
}

