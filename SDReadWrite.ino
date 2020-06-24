#include <SD.h>

/*
此例子展示如果记录三个模拟引脚数值到SD卡，使用SD库。
         
电路部分
* 模拟引脚使用模拟口0,1,2大家可以根据情况接入模拟传感器，
   如果没有，也可以完成此实验，只不过数值是不停跳动的干扰源。
* SD卡与arduino控制板使用SPI总线连接
** MOSI - pin 11 (51)
** MISO - pin 12 (50)
** CLK - pin 13 (52)
** CS - pin 4 (53)
*/

// CS引脚为pin4，这里也沿用官方默认设置
const int chipSelect = 4;  //设定CS接口

void setup()
{
  Serial.begin(9600);  //设置串口通信波特率为9600
  Serial.print("Initializing SD card...");  //串口输出数据Initializing SD card...
  pinMode(10, OUTPUT);
  
  
  if (!SD.begin(chipSelect)) {  //如果从CS口与SD卡通信失败，串口输出信息Card failed, or not present
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");  //与SD卡通信成功，串口输出信息card initialized.
}

void loop()
{
  // 定义数组
  String dataString = "";

  // 读取三个传感器值，写入数组
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

  // 打开文件，注意在同一时间只能有一个文件被打开
  // 如果你要打开另一个文件，就需要先关闭前一个
  File dataFile = SD.open("datalog.txt", FILE_WRITE);  

  // 打开datalog.txt文件，读写状态，位置在文件末尾。
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // 数组dataString输出到串口
    Serial.println(dataString);
  }  
  // 如果无法打开文件，串口输出错误信息error opening datalog.txt
  else {
    Serial.println("error opening datalog.txt");
  }
}
