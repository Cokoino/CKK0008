#include <cobit.h>

cobit Car;
int speed = 2;
int turnSpeed = 1;

/***************************************************************/
void setup(){
  //Serial.begin(9600);
  Car.Reset_chip();                         //Reset N76E003. This function must be used once within the setup function.
  delay(100);
}

/***************************************************************/
void loop(){
  if(Car.Left_LineDetection() == 1 && Car.Right_LineDetection() == 1){
	  Car.Left_light(OFF);
	  Car.Right_light(OFF);
	  Car.Run_Forward(speed);
  }
  
  if(Car.Left_LineDetection() == 1 && Car.Right_LineDetection() == 0){
	  Car.Right_light(ON);
	  Car.Turn_Left(turnSpeed);
  }
  
  if(Car.Left_LineDetection() == 0 && Car.Right_LineDetection() == 1){
	  Car.Left_light(ON);
	  Car.Turn_Right(turnSpeed);
  }
  
  if(Car.Left_LineDetection() == 0 && Car.Right_LineDetection() == 0){
	  Car.Left_light(ON);
	  Car.Right_light(ON);
	  Car.Stop();
  }
  delay(100);
}
