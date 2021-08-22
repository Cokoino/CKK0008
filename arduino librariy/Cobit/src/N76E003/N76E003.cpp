#include "N76E003.h"
#include <Arduino.h>
#include <Wire.h>

////////////////////////////////////////////
N76E003::N76E003(){
  Wire.begin();                             // join i2c bus (address optional for master)
  
  pinMode(5,OUTPUT);                        //left led
  pinMode(6,OUTPUT);                        //right led
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}

////////////////////////////////////////////
int N76E003::Read_(int SensorAdress, int data1, int data2, int data3){
  int data;
  Wire.beginTransmission(Slave_address);    // Send the start signal, and then send the slave address #0x20
  Wire.write(SensorAdress);                 // send sensor address 
  Wire.write(data1);                        // placeholder 
  Wire.write(data2);                        // placeholder 
  Wire.write(data3);                        // placeholder 
  Wire.endTransmission();                   // stop transmitting
  
  Wire.requestFrom(Slave_address, 1);       // Send the start signal, and then request 1 bytes from slave device #0x20
  while (Wire.available()) {                // slave may send less than requested
    data = Wire.read();                     // receive a byte as character
  } 
  return data;
}

////////////////////////////////////////////
void N76E003::Write(int SensorAdress, int data1, int data2, int data3){
  Wire.beginTransmission(Slave_address);    // Send the start signal, and then send the slave address #0x20
  Wire.write(SensorAdress);                 // send sensor address 
  Wire.write(data1);                        // send data  
  Wire.write(data2);                        // send data  
  Wire.write(data3);                        // send data 
  Wire.endTransmission();                   // stop transmitting  
}

////////////////////////////////////////////
void N76E003::Reset_chip(){
  Write(Reset, 0x00, 0x00, 0x00); 
}

////////////////////////////////////////////
void N76E003::Left_Wheel_brake(void){
  Write(LeftWheel, LeftWheelBrake, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Right_Wheel_brake(void){
  Write(RightWheel, RightWheelBrake, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Left_Wheel_CW(){
  Write(LeftWheel, LeftWheelCW, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Left_Wheel_CCW(){
  Write(LeftWheel, LeftWheelCCW, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Right_Wheel_CW(){
  Write(RightWheel, RightWheelCW, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Right_Wheel_CCW(){
  Write(RightWheel, RightWheelCCW, 0x00, 0x00);
}
    
////////////////////////////////////////////
void N76E003::Left_Wheel_Speed(int speed){
  Write(LeftWheel, LeftWheelSpeed, speed, 0x00);
}

////////////////////////////////////////////
void N76E003::Right_Wheel_Speed(int speed){
  Write(RightWheel, RightWheelSpeed, speed, 0x00);
}

////////////////////////////////////////////
void N76E003::Left_Wheel_Step(unsigned int step){
  int H_dat = 0;
  int L_dat = 0;
  if(step<0 || step>65535)
    return;
  H_dat = step/256;
  L_dat = step%256;
  Write(LeftWheel, LeftWheelStep, H_dat, L_dat);
}

////////////////////////////////////////////
void N76E003::Right_Wheel_Step(unsigned int step){
  int H_dat = 0;
  int L_dat = 0;
  if(step<0 || step>65535)
    return;
  H_dat = step/256;
  L_dat = step%256;
  Write(RightWheel, RightWheelStep, H_dat, L_dat);
}

// Mode = 1, Step mode. Mode = 2, Keep on run mode.
////////////////////////////////////////////
void N76E003::Left_Wheel_Mode(int mode){
  if(mode != 1 && mode != 2)
    return;
  Write(LeftWheel, LeftWheelMode, mode, 0x00);
}

// Mode = 1, Step mode. Mode = 2, Keep on run mode.
////////////////////////////////////////////
void N76E003::Right_Wheel_Mode(int mode){
  if(mode != 1 && mode != 2)
    return;
  Write(RightWheel, RightWheelMode, mode, 0x00);
}

////////////////////////////////////////////
void N76E003::Sonar_On(){
  Write(Sonar, SonarOn, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Sonar_Off(){
  Write(Sonar, SonarOff, 0x00, 0x00);
}

// unit CM, maximum is 255cm
////////////////////////////////////////////
int N76E003::Sonar_Measurement_Distance(){
  int distance = Read_(Sonar, SonarRead, 0x00, 0x00);
  return distance;
}

////////////////////////////////////////////
void N76E003::Buzzer_On(){
  Write(Buzzer, BuzzerOn, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Buzzer_Off(){
  Write(Buzzer, BuzzerOff, 0x00, 0x00);
}

// frequency = 20-1K
////////////////////////////////////////////
void N76E003::Buzzer_Frequency(int frequency){
  if(frequency < 20 || frequency > 1000)
    return;
  Write(Buzzer, BuzzerFrequency, frequency/256, frequency%256);
}

////////////////////////////////////////////
void N76E003::Buzzer_Volume(int volume){
  if(volume < 0 || volume > 9)
    return;
  Write(Buzzer, BuzzerVolume, volume, 0x00);
}

////////////////////////////////////////////
void N76E003::All_Servo_On(){
  Write(Servo, ServoOn, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::All_Servo_Off(){
  Write(Servo, ServoOff, 0x00, 0x00);
}

////////////////////////////////////////////
void N76E003::Servo1_Degree(int degree){
  if(degree < 0 || degree > 180)
    return;
  Write(Servo, Servo1, degree, 0x00);
}

////////////////////////////////////////////
void N76E003::Servo2_Degree(int degree){
  if(degree < 0 || degree > 180)
    return;
  Write(Servo, Servo2, degree, 0x00);
}

////////////////////////////////////////////
void N76E003::Servo3_Degree(int degree){
  if(degree < 0 || degree > 180)
    return;
  Write(Servo, Servo3, degree, 0x00);
}
