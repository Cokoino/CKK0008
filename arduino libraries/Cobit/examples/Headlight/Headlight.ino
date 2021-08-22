#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
}

/***************************************************************/
void loop(){
  Car.Left_light(ON);           //parameter = ON or OFF
  Car.Right_light(ON);          //parameter = ON or OFF
  delay(1000);
  Car.Left_light(OFF);           //parameter = ON or OFF
  Car.Right_light(OFF);          //parameter = ON or OFF
  delay(1000);
}
