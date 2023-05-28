#include <SPI.h>  
#include "RF24.h"
#include <Wire.h>
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};
float X_out;
float Y_out;
float Z_out;
int ADXL345 = 0x53;
struct package
{
  // int id=1;
  // float temperature = 18.3;
  // char  text[100] = "Jorge o duck chegou ao destino";
  float xAxis = 0;
  float yAxis = 0;
  float zAxis = 0;
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  delay(1000);  
 //ADXL:
  Wire.begin(); // Initiate the Wire library
    // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);


  //Radio:
  myRadio.begin();  
  myRadio.setChannel(81); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  Serial.println("//////");
  Serial.print("X: ");
  Serial.println(data.xAxis);
  Serial.print("Y: ");
  Serial.println(data.yAxis);
  Serial.print("Z: ");
  Serial.println(data.zAxis);


  X_out = ( Wire.read()| Wire.read() << 8);
  data.xAxis = X_out = (X_out/256)*9.81;
  Y_out = ( Wire.read()| Wire.read() << 8);
  data.yAxis = Y_out = (Y_out/256)*9.81;
  Z_out = ( Wire.read()| Wire.read() << 8);
  data.zAxis = Z_out = (Z_out/256)*9.81;

  myRadio.write(&data, sizeof(data)); 
  
  
}
