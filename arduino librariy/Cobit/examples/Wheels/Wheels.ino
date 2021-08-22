#include <cobit.h>
/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * Designer ：jalen
 * Date：2021-6-12
 */
 
cobit Car;

/***************************************************************/
void setup(){
  Car.Reset_chip();                 // Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  //use for left wheels
  //Car.Left_Wheel_Mode(1);         // Mode = 1, Step mode. Mode = 2, Keep on run mode.
  //Car.Left_Wheel_CW();            // The left wheel turns clockwise
  //Car.Left_Wheel_CCW();           // The left wheel turns counterclockwise
  //Car.Left_Wheel_Speed(1);        // speed = 0-4
  //Car.Left_Wheel_Step(4);         // step = 0-65535, The step unit is 0.9 degrees.
  //Car.Left_Wheel_brake();         // The left wheel brake
  
  //use for right wheels
  //Car.Right_Wheel_Mode(1);        // Mode = 1, Step mode. Mode = 2, Keep on run mode.
  //Car.Right_Wheel_CW();           // The right wheel turns clockwise
  //Car.Right_Wheel_CCW();          // The right wheel turns counterclockwise
  //Car.Right_Wheel_Speed(1);       // speed = 0-4
  //Car.Right_Wheel_Step(4);        // step = 0-65535, The step unit is 0.9 degrees.
  //Car.Right_Wheel_brake();        // The right wheel brake 
}

/***************************************************************/
void loop(){
  Car.Left_Wheel_Mode(1);
  Car.Right_Wheel_Mode(1);
  Car.Left_Wheel_CW();
  Car.Right_Wheel_CW();
  Car.Left_Wheel_Speed(2);
  Car.Right_Wheel_Speed(2);  
  delay(5000);
  Car.Left_Wheel_Speed(0);   //stop
  Car.Right_Wheel_Speed(0);  //stop
  delay(1000);
  Car.Left_Wheel_CCW();
  Car.Right_Wheel_CCW();
  Car.Left_Wheel_Speed(2);
  Car.Right_Wheel_Speed(2); 
  delay(5000);
  Car.Stop();
  Car.Left_Wheel_Speed(0);   //stop
  Car.Right_Wheel_Speed(0);  //stop
  delay(1000);
}
