#include <cobit.h>

cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);          // start serial for output
  Car.Reset_chip();            //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  Car.All_Servo_On();          //Start the servo motor.
  Car.Servo1_Degree(0);        //degree=0--180
  Car.Servo2_Degree(0);        //degree=0--180
  Car.Servo3_Degree(0);        //degree=0--180
  //Car.All_Servo_Off();       //Shut down the servo motor.
}

/***************************************************************/
void loop(){
  Car.Servo1_Degree(90);        
  Car.Servo2_Degree(90);        
  Car.Servo3_Degree(90);  
  delay(500);
}
