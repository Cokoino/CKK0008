#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);
  delay(100);
}

/***************************************************************/
void loop(){
  if(Car.Left_LineDetection() == 1)
	  Serial.println("left not detected");
  else
	  Serial.println("left detected");
  
  if(Car.Right_LineDetection() == 1)
	  Serial.println("right not detected");
  else
	  Serial.println("right detected");
  delay(500);
  Serial.println("");
}
