/*
 * mobile phone communicates with Cobit
 * button format: 0xff-data-0x00-0xff
 * slider format: 0xff-data-0x(0a-0e)-0xff
 * accelerometer format: 0xff-dataX-dataY-dataZ-0x14-0xff
 * ----data > 100 : real data = -(data-100)/10
 * ----data < 100 : real data = data/10
 * Designer ：jalen
 * Date：2021-9-3
 */

#define Pixel
#define BLUETOOTH
#include <cobit.h>

#define PIN        4              // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS  4              // How many NeoPixels are attached to the Arduino? 
NeoPixel pixels(NUMPIXELS, PIN);  //Create a NeoPixel light string class.

cobit Car;
int speed = 3;

boolean lightSW = false;
boolean sonrCarSW = false;

void setup(){ 
  Car.Reset_chip();                    //Reset N76E003. This function must be used once within the setup function.
  Car.Buzzer_Volume(3);           // Set the volume of buzzer, level:0--9
  Car.Buzzer_Frequency(600);      // frequency = 20-1K
  
  pixels.begin();                      // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50);            // Change the brightness of the light. 0-255 level
  //int brightness = getBrightness();  // Gets the brightness of the lamp. 
  //pixels.clear();                    // The memory that fills the entire Neopixel strip is 0 / black/off.
  
  Serial.begin(9600);  
  BluetoothInit();
}

/***************************************************************/
void loop() {
	BluetoothRead();
	for(int i = 0; i<6; i++){
	Serial.println(bCmd[i]);
	}
	
	if(bCmd[1]==b_Button){
		switch(bCmd[2]){
			case b_Up     : Car.Run_Forward(speed);     break;
			case b_Down   : Car.Run_Backward(speed);    break;
			case b_Left   : Car.Turn_Left(speed);       break;
			case b_Right  : Car.Turn_Right(speed);      break;
			case b_Center : Car.Stop();                 break;
			case b_Horn   : Car.Buzzer_On();  
							delay(500);
							Car.Buzzer_Off();           break;
			case b_Red        : sonrCarSW = ~sonrCarSW; break;
			case b_Red        : RGB(255,  0,  0);       break;
			case b_Green      : RGB(  0,255,  0);       break;
			case b_Blue       : RGB(  0,  0,255);       break;
			case b_purple     : RGB(191, 36,156);       break;
			case b_Seagreen   : RGB( 22,205,191);       break;
			case b_Yellow     : RGB(255,255,  0);       break;
			case b_Grey       : RGB(192,192,192);       break;
			case b_DarkPurple : RGB(148,113,179);       break;
			case b_Exchange   : RGB_off();              break;	
			case b_Light  : light(lightSW = ~lightSW);  break;
			default : break;
		}	
	}
	
	if(bCmd[1]==b_Slide){
		
	}
	
	if(bCmd[1]==b_XYZ){
		
	}
	
	if(sonrCarSW){
		sonar_car();
	}
}

/***************************************************************/
void light(boolean sw){
  if(sw){
	Car.Left_light(ON); 
	Car.Right_light(ON);
  }
  else{
	Car.Left_light(OFF); 
	Car.Right_light(OFF);
  }
}

/***************************************************************/
void RGB(int r, int g, int b){
  for(char i = 0; i<4; i++){
	  pixels.setPixelColor(i, pixels.Color(r, g, b));
	  pixels.show();
	  delay(10);
  }  
}

/***************************************************************/
void RGB_off(void){
  for(char i = 0; i<4; i++){
	  pixels.setPixelColor(i, pixels.Color(0, 0, 0));
	  pixels.show();
	  delay(10);
  }  
}

/***************************************************************/
#define distance_minimum 5
int distance_L,distance_R;
int speed1 = 2;
int randNumber=0;

void sonar_car(){
	int distance = 0;
	distance = Car.Sonar_Measurement_Distance();  //Sonar data refresh rate = 50ms
	if(distance>distance_minimum){
		Car.Run_Forward(speed1);
	}
	if(distance<=distance_minimum){
		Car.Stop();
		sweep();
		if((distance_L<=distance_minimum)&&(distance_R<=distance_minimum)){
			Car.Turn_Right_Degree(180,speed1);
			Car.Delay_degree(180, speed1);
			}
		if(distance_R<distance_L){
			Car.Turn_Left_Degree(90,speed1);
			Car.Delay_degree(90, speed1);
			}
		if(distance_R>distance_L){
			Car.Turn_Right_Degree(90,speed1);
			Car.Delay_degree(90, speed1);
			
		if(distance_R==distance_L){
			randNumber = random(1, 2);  //产生随机数
			if(randNumber==1){
				Car.Turn_Left_Degree(90,speed1);
				Car.Delay_degree(90, speed1);
				}
			if(randNumber==2){
			Car.Turn_Right_Degree(180,speed1);
			Car.Delay_degree(180, speed1);
			  }
		};   
	}
    delay(200);
}

void sweep(void)
{
	Car.Turn_Left_Degree(90,speed1);
	Car.Delay_degree(90, speed1); 
	distance_L = Car.Sonar_Measurement_Distance();
	delay(500); 

	Car.Turn_Right_Degree(180,speed1);
	Car.Delay_degree(180, speed1); 
	distance_R = Car.Sonar_Measurement_Distance();
	delay(500);

	Car.Turn_Left_Degree(90,speed1);
	Car.Delay_degree(90, speed1);
}
