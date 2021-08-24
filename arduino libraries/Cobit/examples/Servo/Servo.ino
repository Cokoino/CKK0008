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
  for(int Degree = 0; Degree <=180; Degree ++){   //0 to 180 degrees.
  Car.Servo1_Degree(Degree);        
  Car.Servo2_Degree(Degree);        
  Car.Servo3_Degree(Degree); 
  Serial.println(Degree);  
  delay(20);
  }
  for(int Degree = 180; Degree > 0; Degree --){  //180 to 0 degrees.
  Car.Servo1_Degree(Degree);        
  Car.Servo2_Degree(Degree);        
  Car.Servo3_Degree(Degree); 
  Serial.println(Degree);  
  delay(20);
  }
}
