#include <SPI.h>  
#include "RF24.h" 
#include <Wire.h>
RF24 myRadio (7, 8); 
struct package
{
  float xAxis = 0;
  float yAxis = 0;
  float zAxis = 0;
};

byte addresses[][6] = {"0"}; 



typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{

  if ( myRadio.available())  
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.println("Leitura:");
    Serial.println(data.xAxis);
    Serial.println(data.yAxis);
    Serial.println(data.zAxis);
    Serial.println("cabo a leitura");
    if(data.yAxis < -4){
      Serial.println("Frente");
    }
     if(data.xAxis >= 7){
      Serial.println("Direita");
    }
      if(data.xAxis <= -7){
      Serial.println("Esquerda");
    }
  }
}
