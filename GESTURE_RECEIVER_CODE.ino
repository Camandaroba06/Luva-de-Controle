#include <SPI.h>  
#include "RF24.h" 
#include <Wire.h>
#define motor1_in1 3
#define motor1_in2 5
#define motor2_in1 6
#define motor2_in2 9
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
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
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

    if(data.yAxis < -6){
      Serial.println("--------");
      Serial.println("Frente");
      digitalWrite(motor1_in1, HIGH);
      digitalWrite(motor1_in2, LOW);

      digitalWrite(motor2_in1, HIGH);
      digitalWrite(motor2_in2, LOW);
    }
     else if(data.xAxis >= 7){
      Serial.println("--------");
      Serial.println("Direita");
      digitalWrite(motor1_in1, LOW);
      digitalWrite(motor1_in2, HIGH);

      digitalWrite(motor2_in1, HIGH);
      digitalWrite(motor2_in2, LOW);
    }
      else if(data.yAxis >= 7 ){
      Serial.println("--------");
      Serial.println("tras");
      digitalWrite(motor1_in1, LOW);
      digitalWrite(motor1_in2, HIGH);

      digitalWrite(motor2_in1, LOW);
      digitalWrite(motor2_in2, HIGH);
    }
    else if(data.xAxis < -7){
      Serial.println("--------");
      Serial.println("Esquerda");
      digitalWrite(motor1_in1, HIGH);
      digitalWrite(motor1_in2, LOW);

      digitalWrite(motor2_in1, LOW);
      digitalWrite(motor2_in2, HIGH);
    }
    else {
      digitalWrite(motor1_in1, LOW);
      digitalWrite(motor1_in2, LOW);

      digitalWrite(motor2_in1, LOW);
      digitalWrite(motor2_in2, LOW);      
    }
  }

  

}
