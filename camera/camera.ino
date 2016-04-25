#include <Adafruit_VC0706.h>
#include <SD.h>

#include <SoftwareSerial.h>

#define chipSelect 10
#define Button 7  //定义拍照按钮针脚为7
int ButtonVal = 0; //变量ButtonVal用来存储拍照按钮状态


#if ARDUINO >= 100
// 定义虚拟串口,对于Uno板摄像头TX脚连到Digital pin 2, 摄像头RX脚连到Digital pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(2, 3);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

void setup() {

  // 使用硬件SPI时, SS必须设为输出
#if !defined(SOFTWARE_SPI)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if (chipSelect != 53) pinMode(53, OUTPUT); // 使用mega2560时SS设置
#else
  if (chipSelect != 10) pinMode(10, OUTPUT); // 使用UNO时SS设置

#endif
#endif

  //串口监控输出及定义:

  Serial.begin(9600);
  pinMode(Button, INPUT);
  Serial.println("VC0706 Camera snapshot test");

  // 判断SD卡是否插入并初始化:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // 停止:
    return;
  }

  // 初始化摄像头
  if (cam.begin()) {
    Serial.println("Camera Found:");
  } else {
    Serial.println("No camera found?");
    return;
  }
  // 输出摄像头版本
  char *reply = cam.getVersion();
  if (reply == 0) {
    Serial.print("Failed to get version");
  } else {
    Serial.println("-----------------");
    Serial.print(reply);
    Serial.println("-----------------");
  }

  // 设置拍照尺寸,可设为640x480, 320x240及160x120
  // 尺寸越大数据传输时间越长!

  cam.setImageSize(VC0706_640x480);        // biggest
  //cam.setImageSize(VC0706_320x240);        // medium
  //cam.setImageSize(VC0706_160x120);          // small

  // 可从摄像头读取图片大小

  uint8_t imgsize = cam.getImageSize();
  Serial.print("Image size: ");
  if (imgsize == VC0706_640x480) Serial.println("640x480");
  if (imgsize == VC0706_320x240) Serial.println("320x240");
  if (imgsize == VC0706_160x120) Serial.println("160x120");

}

void loop() {
  //按拍照按钮拍一张照片
  ButtonVal = digitalRead(Button);
  if (ButtonVal == HIGH) {
    Serial.println("Snaping Picture...");
    delay(20);

    if (! cam.takePicture())
      Serial.println("Failed to snap!");
    else
      Serial.println("Picture taken!");

    // 以IMAGExx.JPG为文件名创建图片文件
    char filename[13];
    strcpy(filename, "IMAGE00.JPG");
    for (int i = 0; i < 99; i++) {
      filename[5] = '0' + i / 10;
      filename[6] = '0' + i % 10;
      if (! SD.exists(filename)) {
        break;
      }
    }

    // 打开图像文件并写入
    File imgFile = SD.open(filename, FILE_WRITE);

    // 获取图像文件大小
    uint16_t jpglen = cam.frameLength();
    Serial.print("Storing ");
    Serial.print(jpglen, DEC);
    Serial.print(" byte image.");

    int32_t time = millis();
    pinMode(8, OUTPUT);
    // 读数据到 # bytes!
    byte wCount = 0; // 计数 # 来写
    while (jpglen > 0) {
      // 一次读取 32 bytes;
      uint8_t *buffer;
      uint8_t bytesToRead = min(32, jpglen);

      buffer = cam.readPicture(bytesToRead);
      imgFile.write(buffer, bytesToRead);
      if (++wCount >= 64) { // 每2K发个反馈,以避免出现锁定现象
        Serial.print('.');
        wCount = 0;
      }
      //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");
      jpglen -= bytesToRead;
    }
    imgFile.close();

    time = millis() - time;
    Serial.println("done!");
    Serial.print(time); Serial.println(" ms elapsed");
  }
  cam.begin();  //摄像头重新初始清缓存
  ButtonVal = 0; //按钮值重新设为低
}
