#include <cobit.h>
/*
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Designer ：jalen
 * Date：2021-6-12
 */
#define distance_minimum 20
int distance,distance_10,distance_170;
int speed = 3;
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
  if(Car.Battery_Voltage() >= 6.5){
	  int distance = 0;
	  distance = Car.Sonar_Measurement_Distance();  //Sonar data refresh rate = 50ms
	  if(distance>distance_minimum){
		Car.Run_Forward(speed);
		}
	  if(distance<=distance_minimum){
		Car.Stop();
		sweep();
		if((distance_10<=distance_minimum)&&(distance_170<=distance_minimum)){
			Car.Run_Backward(speed);
			delay(1000);
		}
		if(distance_10<distance_170){
			Car.Turn_Left(speed);
		}
		if(distance_10>distance_170){
			Car.Turn_Right(speed);
		}
		if(distance_10==distance_170){
		  randNumber = random(1, 2);  //产生随机数
		  if(randNumber==1){
			  Car.Turn_Left(speed);
		  }
		  if(randNumber==2){
			  Car.Turn_Right(speed);
		  }
		}
		delay(500); 
		Car.Stop();   
	  }
  }
  powerWarning();
}

/***************************************************************/
void sweep(void)
{
Car.Turn_Left_Degree(80,speed);
delay(1000); 
distance_10 = Car.Sonar_Measurement_Distance();

Car.Turn_Right_Degree(160,speed);
delay(1000); 
distance_170 = Car.Sonar_Measurement_Distance();

Car.Turn_Left_Degree(80,speed);
}

/***************************************************************/
void powerWarning(void){
	if(Car.Battery_Voltage()<6.5){
		Car.Buzzer_On();
	}
	else{
		Car.Buzzer_Off();
	}
}