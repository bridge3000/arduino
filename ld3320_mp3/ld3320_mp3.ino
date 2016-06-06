#include "ld3320.h"

int nMp3Size = 500;
int nMp3Pos = 0;
int bMp3Play = 0;
int EX0 = 0;

void setup() {
  LD_Init_MP3();
  LD_play();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void LD_Init_MP3()
{
//  nLD_Mode = LD_MODE_MP3;
//  LD_Init_Common();
  writeReg(0xBD, 0x02);
  writeReg(0x17, 0x48);
  delay(10);
  
  writeReg(0x85, 0x52);
  writeReg(0x8F, 0x00);
  writeReg(0x81, 0x00);
  writeReg(0x83, 0x00);
  writeReg(0x8E, 0xff);
  writeReg(0x8D, 0xff);
  delay(1);
  writeReg(0x87, 0xff);
  writeReg(0x89, 0xff);
  delay(1);
  writeReg(0x22, 0x00);
  writeReg(0x23, 0x00);
  writeReg(0x20, 0xef);
  writeReg(0x21, 0x07);
  writeReg(0x24, 0x77);
  writeReg(0x25, 0x03);
  writeReg(0x26, 0xbb);
  writeReg(0x27, 0x01);
}


//void LD_AdjustMIX2SPVolume(uint8 val)
//{
//  uint8 ucTmp;
//  ucSPVol = val;
//  val = ((15 - val) & 0x0f) << 2;
//  writeReg(0x8E, val | 0xc3);
//}

void LD_play()
{
  nMp3Pos = 0;
  bMp3Play = 1;
  if (nMp3Pos >= nMp3Size)
    return ;
    
  LD_ReloadMp3Data();
  writeReg(0xBA, 0x00);
  writeReg(0x17, 0x48);
  writeReg(0x33, 0x01);
  writeReg(0x29, 0x04);
  writeReg(0x02, 0x01);
  writeReg(0x85, 0x5A);
  EX0 = 1;
}

void LD_ReloadMp3Data()
{
//  uint32 nCurMp3Pos;
//  uint8 val;
//  uint8 k;
//  nCurMp3Pos = nMp3StartPos + nMp3Pos;
//  FLASH_CS = 1;
//  FLASH_CLK = 0;
//  FLASH_CS = 0;
//  IO_Send_Byte(W25P_FastReadData); /* read command */
//  IO_Send_Byte(((nCurMp3Pos & 0xFFFFFF) >> 16)); /* send 3 address bytes */
//  IO_Send_Byte(((nCurMp3Pos & 0xFFFF) >> 8));
//  IO_Send_Byte(nCurMp3Pos & 0xFF);
//  IO_Send_Byte(0xFF);
//  ucStatus = LD_ReadReg(0x06);
//
//  while ( !(ucStatus & MASK_FIFO_STATUS_AFULL) &&
//          (nMp3Pos < nMp3Size) )
//  {
//    val = 0;
//    for (k = 0; k < 8; k++)
//    {
//      FLASH_CLK = 0;
//      val <<= 1;
//      FLASH_CLK = 1;
//      val |= FLASH_DO;
//    }
//    writeReg(0x01, val);
//    nMp3Pos++;
//    ucStatus = LD_ReadReg(0x06);
//  }
//  FLASH_CS = 1;
//  FLASH_CLK = 0;
}

