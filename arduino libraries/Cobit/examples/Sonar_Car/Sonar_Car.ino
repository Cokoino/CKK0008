#include <cobit.h>
/*
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Designer ：jalen
 * Date：2021-6-12
 */
#define distance_minimum 5
int distance_L,distance_R;
int speed = 2;
int randNumber=0;

cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);             // start serial for output
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  //use for sonar
  Car.Sonar_On();
  delay(100);
  //Car.Sonar_Off();              //turn off sonar
  
  Car.Buzzer_Volume(3);           // Set the volume of buzzer, level:0--9
  Car.Buzzer_Frequency(600);      // frequency = 20-1K
}

/***************************************************************/
void loop(){
	  int distance = 0;
	  distance = Car.Sonar_Measurement_Distance();  //Sonar data refresh rate = 50ms
	  if(distance>distance_minimum){
		Car.Run_Forward(speed);
		}
	  if(distance<=distance_minimum){
		Car.Stop();
		sweep();
		if((distance_L<=distance_minimum)&&(distance_R<=distance_minimum)){
      Car.Turn_Right_Degree(180,speed);
      Car.Delay_degree(180, speed);
		}
		if(distance_R<distance_L){
			Car.Turn_Left_Degree(90,speed);
      Car.Delay_degree(90, speed);
		}
		if(distance_R>distance_L){
			Car.Turn_Right_Degree(90,speed);
      Car.Delay_degree(90, speed);
		}
		if(distance_R==distance_L){
		  randNumber = random(1, 2);  //产生随机数
		  if(randNumber==1){
        Car.Turn_Left_Degree(90,speed);
        Car.Delay_degree(90, speed);
		  }
		  if(randNumber==2){
        Car.Turn_Right_Degree(180,speed);
        Car.Delay_degree(180, speed);
		  }
		};   
	  }
   delay(200);
}

/***************************************************************/
void sweep(void)
{
Car.Turn_Left_Degree(90,speed);
Car.Delay_degree(90, speed); 
distance_L = Car.Sonar_Measurement_Distance();
delay(500); 

Car.Turn_Right_Degree(180,speed);
Car.Delay_degree(180, speed); 
distance_R = Car.Sonar_Measurement_Distance();
delay(500);

Car.Turn_Left_Degree(90,speed);
Car.Delay_degree(90, speed);
}
