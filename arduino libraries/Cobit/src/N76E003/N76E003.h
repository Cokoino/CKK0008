//***********************************************************************************************************
//  N76E885-series I2C slave mode demo code, the Slave address = 0x20
//
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |  UNO R3(M) |          |  N76E003(S) |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//
//  Master communication mode
//  Write: Start + SlaveAddress(W) + SensorAddress + Data(master) + Data(master) + Data(master) + Stop
//  Read : Start + SlaveAddress(W) + SensorAddress + Data(master) + Data(master) + Data(master) + Stop + Start + SlaveAddress(R) + Data(slave) + Stop
//
//***********************************************************************************************************

#ifndef N76E003_h
#define N76E003_h

#include <Arduino.h>
#include <Wire.h>

class N76E003{
  public:
    enum element{
      /////////SlaveAddress/////////
      Slave_address           =    0x20,

      /////////SensorAddress/////////
      LeftWheel               =    0xF1,
      RightWheel              =    0xF2,
      Sonar                   =    0xF3,
      Buzzer                  =    0xF4,
      Servo                   =    0xF5,
      Reset                   =    0xF6,

      /////////Data(master)/////////
      LeftWheelCW             =    0x01,
      RightWheelCW            =    0x02,
      LeftWheelCCW            =    0x03,
      RightWheelCCW           =    0x04,
      SonarOn                 =    0x05,
      BuzzerOn                =    0x06,
      ServoOn                 =    0x07,
      SonarOff                =    0x08,
      BuzzerOff               =    0x09,
      ServoOff                =    0x0A,
      SonarRead               =    0x0B,
      BuzzerFrequency         =    0x0C,
      LeftWheelSpeed          =    0x0D,
      RightWheelSpeed         =    0x0E,
      LeftWheelStep           =    0x0F,
      RightWheelStep          =    0x10,
      LeftWheelMode           =    0x11,
      RightWheelMode          =    0x12,
      Servo1                  =    0x13,
      Servo2                  =    0x14,
      Servo3                  =    0x15,
      BuzzerVolume            =    0x16,
      LeftWheelBrake          =    0x17,
      RightWheelBrake         =    0x18,
    };
    
    N76E003();
    int  Read_(int SensorAdress, int data1, int data2, int data3);        //Master read data form slave
    void Write(int SensorAdress, int data1, int data2, int data3);        //Master write data to slave
    void Reset_chip(void);                                                //reset N76E003, instruction that must be used
    
    //step motor
    void Left_Wheel_brake(void);                               //The left wheel brake. 
    void Right_Wheel_brake(void);                              //The right wheel brake.
    void Left_Wheel_CW(void);                                  //The left wheel turns clockwise. 
    void Left_Wheel_CCW(void);                                 //The left wheel turns counterclockwise.
    void Right_Wheel_CW(void);                                 //The right wheel turns clockwise.
    void Right_Wheel_CCW(void);                                //The right wheel turns counterclockwise.
    void Left_Wheel_Speed(int speed);                          //Speed of left wheel, speed = 0-4
    void Right_Wheel_Speed(int speed);                         //Speed of right wheel, speed = 0-4
    void Left_Wheel_Step(unsigned int step);                   //step = 0-65535, The step unit is 0.9 degrees.
    void Right_Wheel_Step(unsigned int step);                  //step = 0-65535, The step unit is 0.9 degrees.
    void Left_Wheel_Mode(int mode);                            //mode of left wheel, Mode = 1, Step mode. Mode = 2, Keep on run mode.
    void Right_Wheel_Mode(int mode);                           //mode of right wheel, Mode = 1, Step mode. Mode = 2, Keep on run mode.
    
    //sonar
    void Sonar_On();                                           //Turn on sonar
    void Sonar_Off();                                          //Turn off sonar
    int  Sonar_Measurement_Distance();                         //Obtain the sonar measurement distance, data refresh rate = 50ms
    
    //buzzer
    void Buzzer_On();                                          //Turn on buzzer
    void Buzzer_Off();                                         //Turn off buzzer
    void Buzzer_Frequency(int frequency);                      //Set the frequency of buzzer, frequency = 20-1K
    void Buzzer_Volume(int volume);                            //Set the volume of buzzer, level:0--9

    //servo
    void All_Servo_On();                                       //Turn on all servo
    void All_Servo_Off();                                      //Turn off all servo
    void Servo1_Degree(int degree);                            //Set the degree of servo1, degree=0--180
    void Servo2_Degree(int degree);                            //Set the degree of servo2, degree=0--180
    void Servo3_Degree(int degree);                            //Set the degree of servo3, degree=0--180

    private:
    
};

#endif
