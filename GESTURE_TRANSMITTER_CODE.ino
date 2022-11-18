//Arduino Gesture Control Robot
//Reciver Circuit 
//Created BY DIY Builder
//You need to install the required libraries before uploading the code.
//To install the libraries first download the library's zip file then go to sketch > include Library > ADD .ZIP File > Select the downloaded
// libary's Zip file and you're done now. You can upload the the sketch now.
// For more details you can contact me here www.instagram.com/diy.builder


#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include <Wire.h>  // Wire library - used for I2C communication

int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs
RF24 radio(8,10);

const byte address[6]="00001";
struct data{
  int xAxis;
  int yAxis;
  int zAxis;
};
data send_data;

void setup() {
  // put your setup code here, to run once:

//ADXL
Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
Wire.beginTransmission(ADXL345); // Start communicating with the device 
Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
Wire.endTransmission();
delay(10);
//Radio:
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  send_data.xAxis = X_out = (X_out/256)*9.81; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
  send_data.yAxis = Y_out = (Y_out/256)*9.81;
  Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
  send_data.zAxis = Z_out = (Z_out/256)*9.81;
  Serial.println(send_data);

  radio.write(&send_data, sizeof(data));
}
