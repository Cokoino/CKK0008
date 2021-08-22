#include "Font.h"

////////////////////////////////////////////
Drawing::Drawing(){

}

////////////////////////////////////////////
void Drawing::Turn_Left_degree(unsigned int angle, int speed){
  //The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
  //The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
  if(angle > 39910)
    return;

  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);
  
  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  unsigned int step = 0;
  step = (unsigned int)angle/0.604;
  Left_Wheel_CW();
  Left_Wheel_Step(step);
  Right_Wheel_CW();
  Right_Wheel_Step(step);
}

////////////////////////////////////////////
void Drawing::Turn_Right_degree(unsigned int angle, int speed){
  //The distance between the two wheels is 96mm. circumference = 96*3.14 = 301.44mm 
  //The circumference of each degree is 301.44/360 = 0.83733mm. accuracy = 0.51025/0.83733 = 0.609 degree.
  if(angle > 39910)
    return;

  //step mode.
  Left_Wheel_Mode(1);
  Right_Wheel_Mode(1);

  Left_Wheel_Speed(speed);                          
  Right_Wheel_Speed(speed);
  
  unsigned int step = 0;
  step = (unsigned int)angle/0.604;
  Left_Wheel_CCW();
  Left_Wheel_Step(step);
  Right_Wheel_CCW();
  Right_Wheel_Step(step);
}

////////////////////////////////////////////
void Drawing::Pen(boolean ON_OFF){
  if(ON_OFF == true){
	All_Servo_On();
	}
  else{
	All_Servo_Off(); 
	}
}

////////////////////////////////////////////
void Drawing::Pen_Rise(void){
	Servo1_Degree(75);
}
	
////////////////////////////////////////////
void Drawing::Pen_Fall(void){
	Servo1_Degree(105);
}

////////////////////////////////////////////
void Drawing::FontSize(int size){
	if(size < 1 || size > 9)
		return;
	Size = size;
}
	
////////////////////////////////////////////
void Drawing::execute(uint16_t degree, uint16_t pen, uint16_t step, int speed = 1){
	if(degree > 180){
		degree = 360-degree;
		Turn_Left_degree(degree, speed);
	}
	else{
		Turn_Right_degree(degree, speed);
	}	
	switch(speed){
		case 0: break;
		case 1: delay(degree/0.45*10);   break;  //0.45 is the compensation delay.
		case 2: delay(degree/0.45*5);    break;
		case 3: delay(degree/0.45*2.5);  break;
		case 4: delay(degree/0.45*1.25); break;
		default:break;
	}

	if(pen == 1){
		Pen_Fall();
	}
	else{
		Pen_Rise();
	}	
	delay(200);
	Left_Wheel_Mode(1);
	Right_Wheel_Mode(1);  
	Left_Wheel_Speed(speed);                          
	Right_Wheel_Speed(speed);
	Left_Wheel_CCW();
	Left_Wheel_Step(step);
	Right_Wheel_CW();
	Right_Wheel_Step(step);
	switch(speed){
		case 0: break;
		case 1: delay(10*step/0.8);   break;  //0.8 is the compensation delay.
		case 2: delay(5*step/0.8);    break;
		case 3: delay(2.5*step/0.8);  break;
		case 4: delay(1.25*step/0.8); break;
		default:break;
	}
	Pen_Rise();
}

////////////////////////////////////////////
void Drawing::arithmetic(int speed, int num){
  int x,y;
  int angle = 0;
  double distance = 0;

  for(int i = 0; i <= 14; i++){
    if(pgm_read_word_near(run[num]+i) == 0 || i == 14){
      tempData[i+1] = 65;   //65 is the end point.   
      break;
    }
    tempData[i+1] = pgm_read_word_near(run[num]+i);
  }
  
  for(int i=0; i<fontLenth; i++){
	
    //Calculate the distance and Angle between two points.
	x = pgm_read_word_near(dot[tempData[i+1]-1]) - pgm_read_word_near(dot[tempData[i]-1]);
    y = pgm_read_word_near(dot[tempData[i+1]-1]+1) - pgm_read_word_near(dot[tempData[i]-1]+1);
	x = x*Size;
	y = y*Size;
    distance = sqrt((double)x*x + (double)y*y);
	
    if(x > 0 && y < 0){angle = 360 + atan(float(y)/float(x))*T;}   //Based on the Angle of clockwise rotation.   
    if(x < 0 && y < 0){angle = 180 + atan(float(y)/float(x))*T;}   
    if(x > 0 && y > 0){angle = atan(float(y)/float(x))*T;}         
    if(x < 0 && y > 0){angle = 180 + atan(float(y)/float(x))*T;}    
    if(x > 0 && y == 0){angle = 0;  } 
    if(x < 0 && y == 0){angle = 180;} 
    if(x == 0 && y > 0){angle = 90; } 
    if(x == 0 && y < 0){angle = 270;} 
	
	int p;
	if(i != 0){ p = pgm_read_word_near(pen[num]+(i-1));}
	else{p = 0;}
	
    //Perform the corresponding action.
    if(angle >= OldAngle){execute(angle - OldAngle, p, distance, speed);}
    if(angle <  OldAngle){execute(360 - OldAngle + angle, p, distance, speed);}
	
    OldAngle = angle;

    #ifdef TEST
    Serial.print("x : ");
    Serial.println(x);
    Serial.print("y : ");
    Serial.println(y);
    Serial.print("angle : ");
    Serial.println(angle);
    Serial.print("distance : ");
    Serial.println(distance);
    delay(1000);
    #endif
	if(tempData[i+1] == 65){break;}
  }
}

////////////////////////////////////////////
void Drawing::writing(int speed, String str){
  int strLenth;
  strLenth = str.length();
  for(int i=0; i<strLenth; i++){
    switch(str[i]){
      case ' ': arithmetic(speed, 0); break;
      case '!': arithmetic(speed, 1); break;          
      case '"': arithmetic(speed, 2); break;
      case '#': arithmetic(speed, 3); break;
      case '$': arithmetic(speed, 4); break;          
      case '%': arithmetic(speed, 5); break;
      case '&': arithmetic(speed, 6); break;
      case '\'': arithmetic(speed, 7); break;          
      case '(': arithmetic(speed, 8); break;
      case ')': arithmetic(speed, 9); break;
      case '*': arithmetic(speed, 10); break;          
      case '+': arithmetic(speed, 11); break;
      case ',': arithmetic(speed, 12); break;          
      case '-': arithmetic(speed, 13); break;
      case '.': arithmetic(speed, 14); break;
      case '/': arithmetic(speed, 15); break;            
      case '0': arithmetic(speed, 16); break;
      case '1': arithmetic(speed, 17); break;          
      case '2': arithmetic(speed, 18); break;
      case '3': arithmetic(speed, 19); break;
      case '4': arithmetic(speed, 20); break;          
      case '5': arithmetic(speed, 21); break;
      case '6': arithmetic(speed, 22); break;
      case '7': arithmetic(speed, 23); break;          
      case '8': arithmetic(speed, 24); break;
      case '9': arithmetic(speed, 25); break;
      case ':': arithmetic(speed, 26); break;          
      case ';': arithmetic(speed, 27); break;
      case '<': arithmetic(speed, 28); break;
      case '=': arithmetic(speed, 29); break;          
      case '>': arithmetic(speed, 30); break;
      case '?': arithmetic(speed, 31); break;
      case '@': arithmetic(speed, 32); break;
      case 'A': arithmetic(speed, 33); break;
      case 'B': arithmetic(speed, 34); break;
      case 'C': arithmetic(speed, 35); break;
      case 'D': arithmetic(speed, 36); break;
      case 'E': arithmetic(speed, 37); break;
      case 'F': arithmetic(speed, 38); break;
      case 'G': arithmetic(speed, 39); break;
      case 'H': arithmetic(speed, 40); break;
      case 'I': arithmetic(speed, 41); break;
      case 'J': arithmetic(speed, 42); break;
      case 'K': arithmetic(speed, 43); break;
      case 'L': arithmetic(speed, 44); break;
      case 'N': arithmetic(speed, 45); break;
      case 'M': arithmetic(speed, 46); break;
      case 'O': arithmetic(speed, 47); break;
      case 'P': arithmetic(speed, 48); break;
      case 'Q': arithmetic(speed, 49); break;
      case 'R': arithmetic(speed, 50); break;
      case 'S': arithmetic(speed, 51); break;
      case 'T': arithmetic(speed, 52); break;
      case 'U': arithmetic(speed, 53); break;
      case 'V': arithmetic(speed, 54); break;
      case 'W': arithmetic(speed, 55); break;
      case 'X': arithmetic(speed, 56); break;
      case 'Y': arithmetic(speed, 57); break;
      case 'Z': arithmetic(speed, 58); break;
      case '[': arithmetic(speed, 59); break;
      case '\\': arithmetic(speed, 60); break;
      case ']': arithmetic(speed, 61); break;
      case '^': arithmetic(speed, 62); break;
      case '_': arithmetic(speed, 63); break;
      case '`': arithmetic(speed, 64); break;
      case 'a': arithmetic(speed, 65); break;
      case 'b': arithmetic(speed, 66); break;
      case 'c': arithmetic(speed, 67); break;
      case 'd': arithmetic(speed, 68); break;
      case 'e': arithmetic(speed, 69); break;
      case 'f': arithmetic(speed, 70); break;
      case 'g': arithmetic(speed, 71); break;
      case 'h': arithmetic(speed, 72); break;
      case 'i': arithmetic(speed, 73); break;
      case 'j': arithmetic(speed, 74); break;
      case 'k': arithmetic(speed, 75); break;
      case 'l': arithmetic(speed, 76); break;
      case 'n': arithmetic(speed, 77); break;
      case 'm': arithmetic(speed, 78); break;
      case 'o': arithmetic(speed, 79); break;
      case 'p': arithmetic(speed, 80); break;
      case 'q': arithmetic(speed, 81); break;
      case 'r': arithmetic(speed, 82); break;
      case 's': arithmetic(speed, 83); break;
      case 't': arithmetic(speed, 84); break;
      case 'u': arithmetic(speed, 85); break;
      case 'v': arithmetic(speed, 86); break;
      case 'w': arithmetic(speed, 87); break;
      case 'x': arithmetic(speed, 88); break;
      case 'y': arithmetic(speed, 89); break;
      case 'z': arithmetic(speed, 90); break;
      case '{': arithmetic(speed, 91); break;
      case '|': arithmetic(speed, 92); break;
      case '}': arithmetic(speed, 93); break;
      case '~': arithmetic(speed, 94); break;
	  default: break;
    }
  }		
}











