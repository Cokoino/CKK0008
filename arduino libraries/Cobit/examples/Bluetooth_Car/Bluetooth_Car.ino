#define Pixel
#define BLUETOOTH
#include <cobit.h>

#define PIN        4              // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS  4              // How many NeoPixels are attached to the Arduino? 
NeoPixel pixels(NUMPIXELS, PIN);  //Create a NeoPixel light string class.

cobit Car;
int speed = 3;

void setup(){ 
  Car.Reset_chip();                    //Reset N76E003. This function must be used once within the setup function.
  Car.Buzzer_Volume(3);           // Set the volume of buzzer, level:0--9
  Car.Buzzer_Frequency(600);      // frequency = 20-1K
  
  pixels.begin();                      // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50);            // Change the brightness of the light. 0-255 level
  //int brightness = getBrightness();  // Gets the brightness of the lamp. 
  //pixels.clear();                    // The memory that fills the entire Neopixel strip is 0 / black/off.
  
  BluetoothSerial.begin(115200);
}

/***************************************************************/
void loop() {
  if (BluetoothSerial.available()) {
    switch(12){
		case 0xff18e7 : Car.Run_Forward(speed); break;
		case 0xff4ab5 : Car.Run_Backward(speed);break;
		case 0xff10ef : Car.Turn_Left(speed);   break;
		case 0xff5aa5 : Car.Turn_Right(speed);  break;
		case 0xff38c7 : Car.Stop();             break;
		case 0xffa25d : Car.Buzzer_On();        break;
		case 0xff629d : Car.Buzzer_Off();       break;	
		case 0xffe21d : RGB_on();               break;
		case 0xff22dd : RGB_off();              break;	
		case 0xff02fd : Car.Left_light(ON);  Car.Right_light(ON);  break;
		case 0xffc23d : Car.Left_light(OFF); Car.Right_light(OFF); break;	
		default : break;
	}
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

