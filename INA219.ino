#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 sensor;
 
void setup(void) 
{
  Serial.begin(9600);
  sensor.begin();
  Serial.println("Preparing...");
}
 
void loop(void) 
{
  float busVoltage = 0;
  float current = 0; // 以毫安为单位
  float power = 0;
  
  busVoltage = sensor.getBusVoltage_V();//获取电压值
  current = sensor.getCurrent_mA();// 获取电流值
  power = busVoltage * (current/1000);// 计算功率
  
  Serial.print("Bus Voltage:   "); 
  Serial.print(busVoltage);
  Serial.println(" V");
  
  Serial.print("Current:       ");
  Serial.print(current);
  Serial.println(" mA");
  
  Serial.print("Power:         ");
  Serial.print(power);
  Serial.println(" W");
  
  Serial.println("");
  
  delay(2000);
}
