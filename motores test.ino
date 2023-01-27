/*
 *  Code to control two motors using an L298N motor driver and an Arduino
 */

#define motor1_in1 3
#define motor1_in2 5
#define motor2_in1 6
#define motor2_in2 9

void setup() {
  // Set the pin modes for the L298N inputs
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
}

void loop() { 
  // Move motor 1 forward
  digitalWrite(motor1_in1, HIGH);
  digitalWrite(motor1_in2, LOW);
  //delay(10000);
  // Move motor 2 forward
  digitalWrite(motor2_in1, HIGH);
  digitalWrite(motor2_in2, LOW);
//  delay(10000);
//  
//  // Move motor 1 backward
//  digitalWrite(motor1_in1, LOW);
//  digitalWrite(motor1_in2, HIGH);
//  // Move motor 2 backward
//  digitalWrite(motor2_in1, LOW);
//  digitalWrite(motor2_in2, HIGH);
//  delay(1000);
//  
//  // Stop both motors
//  digitalWrite(motor1_in1, LOW);
//  digitalWrite(motor1_in2, LOW);
//  digitalWrite(motor2_in1, LOW);
//  digitalWrite(motor2_in2, LOW);
//  delay(1000);
}
