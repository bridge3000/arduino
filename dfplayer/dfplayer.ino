#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

void setup () {
  Serial.begin (9600);
  mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (5);
}

void loop () {

  mp3_play (3); //play 0001.mp3
  delay (10000); //10 sec, time delay to allow 0001.mp3 to finish playing
}
