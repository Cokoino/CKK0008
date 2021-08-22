#include <cobit.h>
/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * Designer ：jalen
 * Date：2021-8-6
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
  
  //use for left wheels
  //Car.Left_Wheel_Mode(1);             // Mode = 1, Step mode. Mode = 2, Keep on run mode.
  //Car.Left_Wheel_CW();                // The left wheel turns clockwise
  //Car.Left_Wheel_CCW();               // The left wheel turns counterclockwise
  //Car.Left_Wheel_Speed(1);            // speed = 0-4
  //Car.Left_Wheel_Step(4);             // step = 0-65535, The step unit is 0.9 degrees.
  //Car.Left_Wheel_brake();             // The left wheel brake
  
  //use for right wheels
  //Car.Right_Wheel_Mode(1);            // Mode = 1, Step mode. Mode = 2, Keep on run mode.
  //Car.Right_Wheel_CW();               // The right wheel turns clockwise
  //Car.Right_Wheel_CCW();              // The right wheel turns counterclockwise
  //Car.Right_Wheel_Speed(1);           // speed = 0-4
  //Car.Right_Wheel_Step(4);            // step = 0-65535, The step unit is 0.9 degrees.
  //Car.Right_Wheel_brake();            // The right wheel brake 
  
  Car.Pen(true);                        //pen enable or disable
  //Car.Pen_Rise(); 
  //Car.Pen_Fall();
}

/***************************************************************/
void loop(){
  rectangle(200, 100);
}

/***************************************************************/
void rectangle(int length, int width){    //The length and width parameters are in millimeters.
  int speed = 1;
  
  Car.Pen_Fall();
  Car.Run_Forward_Distance(length, speed);   
  Delay_distance(length, speed);
  Car.Pen_Rise();
  
  Car.Turn_Right_Degree(90, speed);
  Delay_degree(90, speed);

  Car.Pen_Fall();
  Car.Run_Forward_Distance(width, speed);   
  Delay_distance(width, speed);
  Car.Pen_Rise();
  
  Car.Turn_Right_Degree(90, speed);
  Delay_degree(90, speed);
  
  Car.Pen_Fall();
  Car.Run_Forward_Distance(length, speed);   
  Delay_distance(length, speed);
  Car.Pen_Rise();
  
  Car.Turn_Right_Degree(90, speed);
  Delay_degree(90, speed);
  
  Car.Pen_Fall();
  Car.Run_Forward_Distance(width, speed);   
  Delay_distance(width, speed);
  Car.Pen_Rise();
}

/***************************************************************/
void Delay_distance(int distance, int speed){     //3.14*65/(360/0.9)=0.51025mm
  switch(speed){
	case 0: break;
	case 1: delay(10*distance/0.5/0.8);   break;  //0.8 is the compensation delay.
	case 2: delay(5*distance/0.5/0.8);    break;
	case 3: delay(2.5*distance/0.5/0.8);  break;
	case 4: delay(1.25*distance/0.5/0.8); break;
	default:break;
  }			
}

/***************************************************************/
//The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
//The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
void Delay_degree(int degree, int speed){         
  switch(speed){
	case 0: break;
	case 1: delay(degree/0.45*10);   break;       //0.45 is the compensation delay.
	case 2: delay(degree/0.45*5);    break;
	case 3: delay(degree/0.45*2.5);  break;
	case 4: delay(degree/0.45*1.25); break;
	default:break;
  }			
}



