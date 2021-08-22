#include <cobit.h>
/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Buzzer can be set frequency range: 20-- 2K Hz.
 * Designer ：jalen
 * Date：2021-6-12
 */
 
cobit Car;

/***************************************************************/
void setup(){
  //Serial.begin(9600);             // start serial for output
  Car.Reset_chip();                   //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  //use for car
  //Car.Brake();                        // Car brake
  //Car.Stop();                         // Car stop
  //Car.Run_Forward(1);                 // Car run forward, parameter is speed = 0-4
  //Car.Run_Backward(1);                // Car run backward, parameter is speed = 0-4
  //Car.Run_Forward_Distance(130, 1);   //parameter 1 is distance = 0-33439mm, accuracy = +/-0.51025mm; parameter 2 is speed = 0-4
  //Car.Run_Backward_Distance(130, 1);  //parameter 1 is distance = 0-33439mm, accuracy = +/-0.51025mm; parameter 2 is speed = 0-4
  //Car.Turn_Left_Degree(unsigned int angle, int speed);               //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
  //Car.Turn_Right_Degree(unsigned int angle, int speed);              //angle = 1-39910, accuracy = +/-0.609 degree; speed = 0-4
}

/***************************************************************/
void loop(){
  Car.Turn_Right_Degree(360, 2);
  Car.Left_light(ON); 
  delay(5000);
  Car.Stop();
  Car.Left_light(OFF); 
  delay(5000);
  powerWarning();
}

/***************************************************************/
void powerWarning(void){
	if(Car.Battery_Voltage()<6.5){
		Car.Buzzer_On();
		Car.Buzzer_Volume(5);
		Car.Buzzer_Frequency(1000);
	}
	else{
		Car.Buzzer_Off();
	}
}
