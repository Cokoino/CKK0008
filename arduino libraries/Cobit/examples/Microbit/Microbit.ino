/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Buzzer can be set frequency range: 20-- 1K Hz, volume: 0-9 level
 * Designer ：jalen
 * Date：2021-6-27
 */
//#define TEST   //For testing code
 
#define IR                       //Include the infrared control library file
#define  Pixel
#define  MICROBIT 
#include <cobit.h>

cobit Car;

//use for IRremote
int RECV_PIN = 3;
IRreceiver irrecv(RECV_PIN);
decode_results results;

#define PIN        4              // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS  4              // How many NeoPixels are attached to the Arduino?
NeoPixel pixels(NUMPIXELS, PIN);  //Create a NeoPixel light string class.
	
/***************************************************************/
void setup(){
  mSerialInit();
  
  irrecv.enableIRIn();            // Start the receiver
  
  #ifdef TEST                     //For testing code.
  Serial.begin(115200);           // start serial for output
  #endif
  
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  pixels.begin();
  pixels.setBrightness(100);
  
  Car.Pen(true);                  
  Car.Pen_Rise(); 
}

/***************************************************************/
void loop(){
  mSerialRead();
  if (irrecv.decode(&results)) {
    irrecv.resume();                                    // Receive the next value
  }
  if(cmdComplete){
	switch(cmd[0]){
		case Reset: 
				Car.Reset_chip();
				mSerialACK();
				break;
		case LeftWheel: 
				if(cmd[1] == Step){
					Car.Left_Wheel_Mode(1);             // Mode = 1, Step mode. Mode = 2, Keep on run mode.
					mSerialACK();
				}
				if(cmd[1] == Continue){
					Car.Left_Wheel_Mode(2);             // Mode = 1, Step mode. Mode = 2, Keep on run mode.
					mSerialACK();
				}		
				if(cmd[1] == CW){
					Car.Left_Wheel_CW();                // The left wheel turns clockwise
					mSerialACK();
				}
				if(cmd[1] == CCW){
					Car.Left_Wheel_CCW();               // The left wheel turns counterclockwise
					mSerialACK();
				}
				if(cmd[1] == Speed){
					Car.Left_Wheel_Speed(cmd[2]);       // speed = 0-4
					mSerialACK();
				}
				if(cmd[1] == TurnDegree){
					Car.Left_Wheel_Step(cmd[2]);          // step = 0-65535, The step unit is 0.9 degrees.
					mSerialACK();
				}
				if(cmd[1] == Distance){
					unsigned step = cmd[2]*1000 + cmd[3];
					Car.Left_Wheel_Step(step);          // step = 0-65535, The step unit is 0.9 degrees.
					mSerialACK();
				}
				if(cmd[1] == Stop){
					Car.Left_Wheel_Speed(0);             // speed = 0-4 
					mSerialACK();
				}
				if(cmd[1] == Brake){
					Car.Left_Wheel_brake();             // The left wheel brake
					mSerialACK();
				}
				break;
		case RightWheel:   
				if(cmd[1] == Step){
					Car.Right_Wheel_Mode(1);             // Mode = 1, Step mode. Mode = 2, Keep on run mode.
					mSerialACK();
				}
				if(cmd[1] == Continue){
					Car.Right_Wheel_Mode(2);             // Mode = 1, Step mode. Mode = 2, Keep on run mode.
					mSerialACK();
				}		
				if(cmd[1] == CW){
					Car.Right_Wheel_CW();                // The Right wheel turns clockwise
					mSerialACK();
				}
				if(cmd[1] == CCW){
					Car.Right_Wheel_CCW();               // The Right wheel turns counterclockwise
					mSerialACK();
				}
				if(cmd[1] == Speed){
					Car.Right_Wheel_Speed(cmd[2]);       // speed = 0-4
					mSerialACK();
				}
				if(cmd[1] == TurnDegree){
					Car.Right_Wheel_Step(cmd[2]);          // step = 0-65535, The step unit is 0.9 degrees.
					mSerialACK();
				}
				if(cmd[1] == Distance){
					unsigned step = cmd[2]*1000 + cmd[3];
					Car.Right_Wheel_Step(step);          // step = 0-65535, The step unit is 0.9 degrees.
					mSerialACK();
				}
				if(cmd[1] == Stop){
					Car.Right_Wheel_Speed(0);             // speed = 0-4
					mSerialACK();
				}
				if(cmd[1] == Brake){
					Car.Right_Wheel_brake();             // The Right wheel brake
					mSerialACK();
				}
				break; 
		case Sonar:  
				if(cmd[1] == On){
					Car.Sonar_On();
					mSerialACK();
				}
				if(cmd[1] == Off){
					Car.Sonar_Off();
					mSerialACK();
				}
				if(cmd[1] == Distance){
					//Serial.println(12);
					mSerialSend(Car.Sonar_Measurement_Distance());
				}
				break;
		case Buzzer:    
				if(cmd[1] == On){
					Car.Buzzer_On();
					mSerialACK();
				}
				if(cmd[1] == Off){
					Car.Buzzer_Off();
					mSerialACK();
				}
				if(cmd[1] == Frequency){
					Car.Buzzer_Frequency(cmd[2]*256+cmd[3]);       // frequency = 20-1K
					mSerialACK();
				}
				if(cmd[1] == Volume){
					Car.Buzzer_Volume(cmd[2]);          // Set the volume of buzzer, level:0--9
					mSerialACK();
				}
				break;
		case Servo: 
				if(cmd[1] == On){
					Car.All_Servo_On();
					mSerialACK();
				}
				if(cmd[1] == Off){
					Car.All_Servo_Off();
					mSerialACK();
				}
				if(cmd[1] == Servo1){
					Car.Servo1_Degree(cmd[2]);
					mSerialACK();
				}
				if(cmd[1] == Servo2){
					Car.Servo2_Degree(cmd[2]);
					mSerialACK();
				}
				if(cmd[1] == Servo3){
					Car.Servo3_Degree(cmd[2]);
					mSerialACK();
				}
				break;
		case LeftHeadlight:
				if(cmd[1] == On){
					Car.Left_light(ON);                 //parameter = ON or OFF
					mSerialACK();
				}
				if(cmd[1] == Off){
					Car.Left_light(OFF);                //parameter = ON or OFF
					mSerialACK();
				}
				break;
		case RightHeadlight: 
				if(cmd[1] == On){
					Car.Right_light(ON);                //parameter = ON or OFF
					mSerialACK();
				}
				if(cmd[1] == Off){
					Car.Right_light(OFF);               //parameter = ON or OFF
					mSerialACK();
				}
				break;
		case LeftPR: 
				mSerialSend(Car.Left_PR());		
				break;
		case RightPR:
				mSerialSend(Car.Right_PR());
				break;
		case LeftLineDetection:
				mSerialSend(Car.Left_LineDetection());
				break;
		case RightLineDetection:
				mSerialSend(Car.Right_LineDetection());
				break;
		case RGB_:
				if(cmd[1] == Brightness){
					pixels.setBrightness(cmd[2]);
					mSerialACK();					
				}
				if(cmd[1] == RGB1){
					pixels.setPixelColor(0, pixels.Color(cmd[2], cmd[3], cmd[4]));
					pixels.show();
					mSerialACK();
				}
				if(cmd[1] == RGB2){
					pixels.setPixelColor(1, pixels.Color(cmd[2], cmd[3], cmd[4]));
					pixels.show();
					mSerialACK();
				}
				if(cmd[1] == RGB3){
					pixels.setPixelColor(2, pixels.Color(cmd[2], cmd[3], cmd[4]));
					pixels.show();
					mSerialACK();
				}
				if(cmd[1] == RGB4){
					pixels.setPixelColor(3, pixels.Color(cmd[2], cmd[3], cmd[4]));
					pixels.show();
					mSerialACK();
				}
				break;				
		case Voltmeter:	
				if(cmd[1] == Analog){
					mSerialSend(Car.Battery_Voltage()*10);
				}
				if(cmd[1] == Percent){
					mSerialSend(Car.Battery_Level());
				}
				break;
		case a0: 
				if(cmd[1] == Input){
					pinMode(A0, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					pinMode(A0, OUTPUT);
					mSerialACK();
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(A0, LOW);}
						if(cmd[3] == 101){digitalWrite(A0, HIGH);}	
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(A0));						
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Analog){
						mSerialSend(map(analogRead(A0), 0, 1023, 0, 255));						
					}
				}
				break;
		case a1: 
				if(cmd[1] == Input){
					pinMode(A1, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					pinMode(A1, OUTPUT);
					mSerialACK();
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(A1, LOW);}
						if(cmd[3] == 101){digitalWrite(A1, HIGH);}	
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(A1));						
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Analog){
						mSerialSend(map(analogRead(A1), 0, 1023, 0, 255));						
					}
				}
				break;
		case a2:
				if(cmd[1] == Input){
					pinMode(A2, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					pinMode(A2, OUTPUT);
					mSerialACK();
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(A2, LOW);}
						if(cmd[3] == 101){digitalWrite(A2, HIGH);}	
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(A2));						
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Analog){
						mSerialSend(map(analogRead(A2), 0, 1023, 0, 255));						
					}
				}		
				break;
		case d11: 
				if(cmd[1] == Input){
					pinMode(11, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					pinMode(11, OUTPUT);
					mSerialACK();
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(11, LOW);}
						if(cmd[3] == 101){digitalWrite(11, HIGH);}
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(11));
					}
				}
				if(cmd[1] == Write){
					if(cmd[2] == Analog){
						analogWrite(11, cmd[3]);
						mSerialACK();
					}
				}				
				break;
		case d12:
				if(cmd[1] == Input){
					pinMode(12, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					mSerialACK();
					pinMode(12, OUTPUT);
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(12, LOW);}
						if(cmd[3] == 101){digitalWrite(12, HIGH);}
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(12));						
					}
				}		
				break;
		case d13: 
				if(cmd[1] == Input){
					pinMode(13, INPUT);
					mSerialACK();
				}
				if(cmd[1] == Output){
					pinMode(13, OUTPUT);
					mSerialACK();
				}
				if(cmd[1] == Write){
					if(cmd[2] == Digital){
						if(cmd[3] == 100){digitalWrite(13, LOW);}
						if(cmd[3] == 101){digitalWrite(13, HIGH);}
						mSerialACK();
					}
				}
				if(cmd[1] == Read){
					if(cmd[2] == Digital){
						mSerialSend(digitalRead(13));
					}
				}				
				break;
		case Car_:
				if(cmd[1] == Stop){
					Car.Stop(); 
					mSerialACK();
				}
				if(cmd[1] == Brake){
					Car.Brake();
					mSerialACK();
				}
				if(cmd[1] == Forward){
					Car.Run_Forward(cmd[2]);     //forward
					mSerialACK();
				}
				if(cmd[1] == Back){
					Car.Run_Backward(cmd[2]);   //back
					mSerialACK();
				}
				if(cmd[1] == Left){
					Car.Turn_Left(cmd[2]);      //turn left
					mSerialACK();
				}
				if(cmd[1] == Right){
					Car.Turn_Right(cmd[2]);     //turn right
					mSerialACK();
				}
				if(cmd[1] == ForwardDistance){
					unsigned int distance = cmd[2]*1000+cmd[3];
					Car.Run_Forward_Distance(distance, cmd[4]); //forward
					mSerialACK();
				}
				if(cmd[1] == BackDistance){
					unsigned int distance = cmd[2]*1000+cmd[3];
					Car.Run_Backward_Distance(distance, cmd[4]);//back
					mSerialACK();
				}
				if(cmd[1] == CW){
					Car.Turn_Right_Degree(cmd[2],cmd[3]);
					mSerialACK();
				}
				if(cmd[1] == CCW){
					Car.Turn_Left_Degree(cmd[2],cmd[3]);
					mSerialACK();					
				}
				break;
		case Font:
				Car.FontSize(cmd[1]);
				String font = " ";
				font[0] = (char)cmd[2];
				Car.writing(1, font);
				mSerialACK();
				break;
		case IRremote:
				if(cmd[1] == Read){
					mSerialSend(results.value);
				}
				break;
		default:break;
	};
	cmdComplete = false;
  }
}
