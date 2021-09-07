#include "cobit.h"
#include <Arduino.h>
#include <Wire.h>

////////////////////////////////////////////
cobit::cobit(){
  Wire.begin();                             // join i2c bus (address optional for master)
  
  pinMode(leftLight,OUTPUT);                // left light
  pinMode(rightLight,OUTPUT);               // right light
  digitalWrite(leftLight,LOW);
  digitalWrite(rightLight,LOW);
  
  pinMode(leftPR,INPUT);                    // Left photoresistive pin of cobit.
  pinMode(rightPR,INPUT);                   // Right photoresistive pin of cobit.
  
  pinMode(leftLineDetction,INPUT);          // The cobit left infrared black and white line detects pin
  pinMode(rightLineDetction,INPUT);         // The cobit right infrared black and white line detects pin
}

////////////////////////////////////////////
void cobit::Brake(void){
  Write(LeftWheel, LeftWheelBrake, 0x00, 0x00);
  Write(RightWheel, RightWheelBrake, 0x00, 0x00);
}

////////////////////////////////////////////
void cobit::Stop(void){
  Write(LeftWheel, LeftWheelSpeed, 0x00, 0x00);
  Write(RightWheel, RightWheelSpeed, 0x00, 0x00);
}

////////////////////////////////////////////
void cobit::Speed(int speed){
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
}

////////////////////////////////////////////
void cobit::Run_Forward(int speed){
  //Keep on run mode.
  Left_Wheel_Mode(2);
  Right_Wheel_Mode(2);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);

  Left_Wheel_CCW();
  Right_Wheel_CW();
}

////////////////////////////////////////////
void cobit::Run_Backward(int speed){
  //Keep on run mode.
  Left_Wheel_Mode(2);
  Right_Wheel_Mode(2);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);

  Left_Wheel_CW();
  Right_Wheel_CCW();
}

////////////////////////////////////////////
void cobit::Turn_Left(int speed){
  //Keep on run mode.
  Left_Wheel_Mode(2);
  Right_Wheel_Mode(2);
 
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);

  Left_Wheel_CW();
  Right_Wheel_CW();
}

////////////////////////////////////////////
void cobit::Turn_Right(int speed){
  //Keep on run mode.
  Left_Wheel_Mode(2);
  Right_Wheel_Mode(2);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);

  Left_Wheel_CCW();
  Right_Wheel_CCW();
}

////////////////////////////////////////////
void cobit::Run_Forward_Distance(unsigned int distance, int speed){
  if(distance > 33439)
    return;
  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  ////////////////////////////////////3.14*65/(360/0.9)=0.51025mm
  unsigned int step = 0;
  step = (unsigned int)distance/0.51025;     //maximum distance is 65535*0.51025=33439.23mm
  Left_Wheel_CCW();
  Left_Wheel_Step(step);
  Right_Wheel_CW();
  Right_Wheel_Step(step);
}
    
////////////////////////////////////////////
void cobit::Run_Backward_Distance(unsigned int distance, int speed){
  if(distance > 33439)
    return;
  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  ////////////////////////////////////3.14*65/(360/0.9)=0.51025mm
  unsigned int step = 0;
  step = (unsigned int)distance/0.51025;     //maximum distance is 65535*0.51025=33439.23mm
  Left_Wheel_CW();
  Left_Wheel_Step(step);
  Right_Wheel_CCW();
  Right_Wheel_Step(step);
}

////////////////////////////////////////////
void cobit::Turn_Left_Degree(unsigned int angle, int speed){
  //The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
  //The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
  if(angle > 39910)
    return;

  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  unsigned int step = 0;
  step = (unsigned int)angle/0.604;
  Left_Wheel_CW();
  Left_Wheel_Step(step);
  Right_Wheel_CW();
  Right_Wheel_Step(step);
}

////////////////////////////////////////////
void cobit::Turn_Right_Degree(unsigned int angle, int speed){
  //The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
  //The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
  if(angle > 39910)
    return;

  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);

  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  unsigned int step = 0;
  step = (unsigned int)angle/0.604;
  Left_Wheel_CCW();
  Left_Wheel_Step(step);
  Right_Wheel_CCW();
  Right_Wheel_Step(step);
}

////////////////////////////////////////////
void cobit::Left_light(boolean ON_OFF){
  if(ON_OFF == true){
	analogWrite(leftLight, 255);
	}
  else{
	analogWrite(leftLight, 0);  
	}	
}

////////////////////////////////////////////
void cobit::Right_light(boolean ON_OFF){
  if(ON_OFF == true){
	analogWrite(rightLight, 255);
	}
  else{
	analogWrite(rightLight, 0);
	}	
}

////////////////////////////////////////////
void cobit::Left_light_brightness(int brightness){
  analogWrite(leftLight, brightness);
}

////////////////////////////////////////////
void cobit::Right_light_brightness(int brightness){
  analogWrite(rightLight, brightness);
}

////////////////////////////////////////////
uint8_t cobit::Left_PR(void){
  return map(analogRead(leftPR), 0, 1023, 0, 255);
}

////////////////////////////////////////////
uint8_t cobit::Right_PR(void){
  return map(analogRead(rightPR), 0, 1023, 0, 255);
}

////////////////////////////////////////////
uint8_t cobit::Left_LineDetection(void){
  return digitalRead(leftLineDetction);
}

////////////////////////////////////////////
uint8_t cobit::Right_LineDetection(void){
  return digitalRead(rightLineDetction);
}

////////////////////////////////////////////
float cobit::Battery_Voltage(void){
  return analogRead(voltageMeter)*0.0049*11;
}

////////////////////////////////////////////
int cobit::Battery_Level(void){
  float volt = analogRead(voltageMeter)*0.0049;
  if(volt < 0.591)       // 6.5V*1K/11K = 0.590909
	return 0;            // 0%
  else if(volt > 0.8 )   // 8.8V*1K/11K = 0.8
    return -1;           // ERR
  else if(volt > 0.763)  // 8.4V*1K/11K = 0.763636
    return 100;          // 100%
  else{
	volt = volt * 1000;
    return map(volt, 591, 763, 0, 100);  // 0-100%
  }
}

////////////////////////////////////////////
void cobit::Delay_distance(int distance, int speed){ //3.14*65/(360/0.9)=0.51025mm
  switch(speed){
	case 0: break;
	case 1: delay(10*distance/0.5/0.8);   break;     //0.8 is the compensation delay.
	case 2: delay(5*distance/0.5/0.8);    break;
	case 3: delay(2.5*distance/0.5/0.8);  break;
	case 4: delay(1.25*distance/0.5/0.8); break;
	default:break;
  }	
}

////////////////////////////////////////////
//The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
//The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
void cobit::Delay_degree(int degree, int speed){
  switch(speed){
	case 0: break;
	case 1: delay(degree/0.45*10);   break;       //0.45 is the compensation delay.
	case 2: delay(degree/0.45*5);    break;
	case 3: delay(degree/0.45*2.5);  break;
	case 4: delay(degree/0.45*1.25); break;
	default:break;
  }
}

////////////////////////////////////////////
void cobit::Wheel_Delay(int step, int speed){
  switch(speed){
	case 0: break;
	case 1: delay(step/0.9*10);   break;       //0.9 is the compensation delay.
	case 2: delay(step/0.9*5);    break;
	case 3: delay(step/0.9*2.5);  break;
	case 4: delay(step/0.9*1.25); break;
	default:break;
  }
}







