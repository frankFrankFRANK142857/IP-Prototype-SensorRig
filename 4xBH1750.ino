//#include <SoftI2CMaster.h>
#include <Wire.h>

unsigned int resu = 0;

int BH1750address = 0x5C; //芯片地址为16位23

byte buff[2]; //从BH1750寄存器读出来的是2个字节的数据，先接收的是高8位[15:8]，后接收的是低8位[7:0]
byte value_high = 0;
byte value_low = 0;

void setup() {
  
    pinMode(41,OUTPUT);
    pinMode(42,OUTPUT);
    pinMode(43,OUTPUT);
    pinMode(44,OUTPUT);
    
    Wire.begin();
    Serial.begin(9600);
}

void loop() {

    for(int i = 41; i <= 44; i++) {

        digitalWrite(i, HIGH);
        
        Wire.beginTransmission(BH1750address);
        Wire.write(0x20);
        Wire.endTransmission();
        delay(180);
    
        Wire.requestFrom(BH1750address, 2);
        value_high = Wire.read();
        value_low = Wire.read();
    
        resu = ((value_high<<8) | value_low)/1.2;
        Serial.print(i - 40);
        Serial.print(" ");
        Serial.println(resu);

        digitalWrite(i, LOW);   
        delay(1000);
        
    }
}
