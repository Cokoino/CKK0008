#include <cobit.h>

cobit Car;
int speed = 3;

/***************************************************************/
void setup(){
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);

  Car.Buzzer_On();
  Car.Buzzer_Frequency(100);     // frequency = 20-1K
  Car.Buzzer_Volume(5);          // Set the volume of buzzer, level:0--9
  //Car.Buzzer_Off();            //turn off buzzer
}

/***************************************************************/
void loop(){
  if(Car.Left_LineDetection() == 1 || Car.Right_LineDetection() == 1){
	  Car.Stop();
	  Car.Buzzer_On();
	  if(Car.Left_LineDetection() == 1 && Car.Right_LineDetection() == 0){
		  Car.Left_light(OFF);
		  Car.Turn_Right(speed);
	  }	

	  if(Car.Left_LineDetection() == 0 && Car.Right_LineDetection() == 1){
		  Car.Right_light(OFF);
		  Car.Turn_Left(speed);
	  }	
	  
      if(Car.Left_LineDetection() == 1 && Car.Right_LineDetection() == 1){
	      Car.Left_light(OFF);
	      Car.Right_light(OFF);
		  Car.Run_Backward(speed); 
      }
  }
  else{
	  Car.Left_light(ON);
	  Car.Right_light(ON);
	  Car.Run_Forward(speed);
	  Car.Buzzer_Off();
  }
}

