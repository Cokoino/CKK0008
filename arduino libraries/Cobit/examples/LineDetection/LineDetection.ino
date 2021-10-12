#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);
  delay(100);
}

/***************************************************************/
void loop(){
  if(Car.Left_LineDetection() == 0)       //The sensor on the left detects a black line.
	  Serial.println("left detected");
  if(Car.Right_LineDetection() == 0)      //The sensor on the right detects a black line.
	  Serial.println("right detected");
  delay(500);
}
