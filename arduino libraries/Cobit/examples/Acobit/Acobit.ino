#include <cobit.h>
/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Buzzer can be set frequency range: 20-- 1K Hz.
 * Designer ：jalen
 * Date：2021-6-12
 */
 
cobit Car;

/***************************************************************/
void setup(){
  //Serial.begin(9600);                     // start serial for output
  Car.Reset_chip();                         //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  //use for car
  //Car.Brake();                            // Car brake
  //Car.Stop();                             // Car stop
  //Car.Run_Forward(int speed);             // Car run forward, parameter is speed = 0-4
  //Car.Run_Backward(int speed);            // Car run backward, parameter is speed = 0-4
  //Car.Turn_Left(int speed);               //Car turn left, speed = 0-4
  //Car.Turn_Right(int speed);              //Car turn right, speed = 0-4
  //Car.Run_Forward_Distance(unsigned int distance, int speed);        //distance = 0-33439mm, accuracy = +/-0.51025mm; speed = 0-4
  //Car.Run_Backward_Distance(unsigned int distance, int speed);       //distance = 0-33439mm, accuracy = +/-0.51025mm; speed = 0-4
  //Car.Turn_Left_Degree(unsigned int angle, int speed);               //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
  //Car.Turn_Right_Degree(unsigned int angle, int speed);              //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
}

/***************************************************************/
void loop(){
  Car.Turn_Left_Degree(360, 2);
  Car.Delay_degree(360, 2);          //Time delay based on rotation angle and speed.
  
  Car.Turn_Right_Degree(360, 2);
  Car.Delay_degree(360, 2);          //Time delay based on rotation angle and speed.

  Car.Run_Forward_Distance(200, 1);
  Car.Delay_distance(200, 1);        //Time delay based on distance traveled and speed.
  Car.Run_Backward_Distance(200, 1);
  Car.Delay_distance(200, 1);        //Time delay based on distance traveled and speed.
  
  Car.Turn_Left(2); 
  delay(1000);
  Car.Stop();
  delay(500);
  Car.Turn_Right(2);
  delay(1000);
  Car.Stop();
  delay(1000);
  
  Car.Run_Forward(2);
  delay(1000);
  Car.Stop();
  delay(500);
  Car.Run_Backward(2);
  delay(1000);
  Car.Stop();
  delay(1000);  
}

