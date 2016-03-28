int DI = 12;
int RW = 11;
int DB[] = {3, 4, 5, 6, 7, 8, 9, 10};//使用数组来定义总线需要的管脚
int Enable = 2;

void LcdCommandWrite(int value) // poll all the pins
{
  int i = 0;
  for (i = DB[0]; i <= DI; i++) //总线赋值
  {
    digitalWrite(i, value & 01);
    value >>= 1;
  }
  digitalWrite(Enable, LOW);
  delayMicroseconds(1); // send a pulse to enable
  digitalWrite(Enable, HIGH);
  delayMicroseconds(1); // pause 1 ms according to datasheet
  digitalWrite(Enable, LOW);
  delayMicroseconds(1); // pause 1 ms according to datasheet
}

void LcdDataWrite(int value) // poll all the pins
{
  int i = 0;
  digitalWrite(DI, HIGH);
  digitalWrite(RW, LOW);
  for (i = DB[0]; i <= DB[7]; i++) {
    digitalWrite(i, value & 01);
    value >>= 1;
  }
  digitalWrite(Enable, LOW);
  delayMicroseconds(1); // send a pulse to enable
  digitalWrite(Enable, HIGH);
  delayMicroseconds(1);
  digitalWrite(Enable, LOW);
  delayMicroseconds(1); // pause 1 ms according to datasheet
}

void setup (void) {
  int i = 0;
  for (i = Enable; i <= DI; i++)
  {
    pinMode(i, OUTPUT);
  }

  delay(100); // initiatize lcd after a short pause needed by the LCDs controller
  LcdCommandWrite(0x38); // set: // 8-bit interface, 1 display lines, 5x7 font
  delay(20);
  LcdCommandWrite(0x06); // entry mode set: // increment automatically, no display shift
  delay(20);
  LcdCommandWrite(0x0E); // display control: // turn display on, cursor on, no blinking
  delay(20);
  LcdCommandWrite(0x01); // clear display, set cursor position to zero
  delay(100);
  LcdCommandWrite(0x80); // display control: // turn display on, cursor on, no blinking
  delay(20);
}

void loop (void) {
  LcdCommandWrite(0x02); // set cursor position to zero
  delay(10); // Write the welcome message
  LcdDataWrite('H');
  LcdDataWrite('o');
  LcdDataWrite('l');
  LcdDataWrite('a');
  LcdDataWrite(' ');
  LcdDataWrite('C');
  LcdDataWrite('a');
  LcdDataWrite('r');
  LcdDataWrite('a');
  LcdDataWrite('c');
  LcdDataWrite('o');
  LcdDataWrite('l');
  LcdDataWrite('a');
  delay(500);
}

