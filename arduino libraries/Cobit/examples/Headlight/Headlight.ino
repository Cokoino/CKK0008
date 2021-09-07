#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
}

/***************************************************************/
void loop(){
  //Turn on the LED for one second, then turn it off.
  Car.Left_light(ON);            //parameter = ON or OFF
  Car.Right_light(ON);           //parameter = ON or OFF
  delay(1000);
  Car.Left_light(OFF);           //parameter = ON or OFF
  Car.Right_light(OFF);          //parameter = ON or OFF
  delay(1000);
  
  //Breath lamp.
  for(int i=0; i<255; i++){
	Car.Left_light_brightness(i);   //brightness = 0-255
	Car.Right_light_brightness(i);  //brightness = 0-255
	delay(10);
  }
  for(int i=255; i>0; i--){
	Car.Left_light_brightness(i);   //brightness = 0-255
	Car.Right_light_brightness(i);  //brightness = 0-255
	delay(10);
  }
  delay(1000);
}
