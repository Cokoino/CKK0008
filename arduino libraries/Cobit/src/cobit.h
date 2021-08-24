/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Buzzer can be set frequency range: 20-- 2K Hz.
 * Designer ：jalen
 * Date：2021-6-27
 */
#ifndef COBIT_h
#define COBIT_h

#include <Arduino.h>
#include <Wire.h>
#include "Font/Font.h"

#ifdef IR
#include "IR/IR.h"
#endif

#ifdef Pixel
#include "NeoPixel/NeoPixel.h"
#endif

#ifdef MICROBIT
#include "Microbit/Microbit.h"
#endif

#ifdef BLUETOOTH
#include <SoftwareSerial.h>
#define RX      8
#define TX      7
SoftwareSerial BluetoothSerial(RX, TX);
#endif

#define leftLight  5
#define rightLight 6

#define leftPR     A6
#define rightPR    A7

#define leftLineDetction     10
#define rightLineDetction    9

#define voltageMeter    A3

#define ON   true
#define OFF  false

enum font_{ 
	turtle   = 1, 
	standard = 2
	};
		
class cobit : public Drawing{
  public: 
    cobit();
    //car
    void Brake(void);                                          //Car brake
    void Stop(void);                                           //Car stop
	void Speed(int speed);                                     //Car speed
    void Run_Forward(int speed);                               //Car run forward, speed = 0-4
    void Run_Backward(int speed);                              //Car run backward, speed = 0-4
    void Turn_Left(int speed);                                 //Car turn left, speed = 0-4
    void Turn_Right(int speed);                                //Car turn right, speed = 0-4
    void Run_Forward_Distance(unsigned int distance, int speed);        //distance = 0-33439mm, accuracy = +/-0.51025mm; speed = 0-4
    void Run_Backward_Distance(unsigned int distance, int speed);       //distance = 0-33439mm, accuracy = +/-0.51025mm; speed = 0-4
    void Turn_Left_Degree(unsigned int angle, int speed);               //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
    void Turn_Right_Degree(unsigned int angle, int speed);              //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
	
	void Left_light(boolean ON_OFF);                           //ON_OFF=true or false
	void Right_light(boolean ON_OFF);
	void Left_light_brightness(int brightness);                //brightness = 0-255
	void Right_light_brightness(int brightness);               //brightness = 0-255
	
	uint8_t Left_PR(void);                                     //Gets the photosensitive resistance value on the left side of the cobit. return:0--255
	uint8_t Right_PR(void);                                    //Gets the photosensitive resistance value on the right side of the cobit. return:0--255
    
	uint8_t Left_LineDetection(void);                          //cobit left infrared black and white line detection.  return: 0 or 1                 
	uint8_t Right_LineDetection(void);                         //cobit Right infrared black and white line detection.  return: 0 or 1  
	
	float Battery_Voltage(void);                               //battery voltage
	int Battery_Level(void);                                   //percent ?%
	
	void Delay_distance(int distance, int speed);              //Time delay based on distance traveled and speed.
	void Delay_degree(int degree, int speed);                  //Time delay based on rotation angle and speed.       
	
    private:
    
};

#endif
