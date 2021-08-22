#define IR          //Include the infrared control library file
#define Pixel
#include <cobit.h>

int RECV_PIN = 3;
IRreceiver irrecv(RECV_PIN);
decode_results results;

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        4 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS  4 
//Create a NeoPixel light string class.
NeoPixel pixels(NUMPIXELS, PIN);

cobit Car;
int speed = 3;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();                 // Start the receiver
  
  Car.Buzzer_Volume(3);                // Set the volume of buzzer, level:0--9
  Car.Buzzer_Frequency(600);           // frequency = 20-1K
  
  Car.All_Servo_On();                  // servo switch
  
  pixels.begin();                      // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50);            // Change the brightness of the light. 0-255 level
  //int brightness = getBrightness();  // Gets the brightness of the lamp. 
  //pixels.clear();                    // The memory that fills the entire Neopixel strip is 0 / black/off.
}

/***************************************************************/
void loop() {
  if (irrecv.decode(&results)) {
    switch(results.value){
		case 0xff18e7 : Car.Run_Forward(speed); break;                      //key: ▲
		case 0xff4ab5 : Car.Run_Backward(speed);break;                      //key: ▼
		case 0xff10ef : Car.Turn_Left(speed);   break;                      //key: ◄
		case 0xff5aa5 : Car.Turn_Right(speed);  break;                      //key: ►
		case 0xff38c7 : Car.Stop();             break;                      //key: OK
		
		case 0xffa25d : Car.Buzzer_On();        break;                      //key: 1
		case 0xff629d : Car.Buzzer_Off();       break;	                    //key: 2
		
		case 0xffe21d : RGB_on();               break;                      //key: 3
		case 0xff22dd : RGB_off();              break;                      //key: 4
		
		case 0xff02fd : Car.Left_light(ON);  Car.Right_light(ON);  break;   //key: 5
		case 0xffc23d : Car.Left_light(OFF); Car.Right_light(OFF); break;	//key: 6
		
		case 0xffe01f : if(speed < 4){
						speed = speed + 1;
						Car.Speed(speed);
						delay(100);
						}       
						break;      										//key: 7
		case 0xffa857 : if(speed > 0){
						speed = speed - 1;
						Car.Speed(speed);
						delay(100);
						}     
						break;	                                            //key: 8
		
		case 0xff6897 : Car.Pen_Rise(); break;                              //key: *    rise
		case 0xffb04f : Car.Pen_Fall(); break;	                            //key: #    fall
		default : break;
	}
    irrecv.resume();            // Receive the next value
  }
}

/***************************************************************/
void RGB_on(void){
  for(char i = 0; i<4; i++){
	  pixels.setPixelColor(i, pixels.Color(250, 200, 155));
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

