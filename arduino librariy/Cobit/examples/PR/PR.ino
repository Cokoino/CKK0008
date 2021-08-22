#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);
  delay(100);
}

/***************************************************************/
void loop(){
  Serial.print("Right:");
  Serial.println(Car.Right_PR());
  Serial.print("Left:");
  Serial.println(Car.Left_PR());
  delay(500);
  Serial.println("");
}
