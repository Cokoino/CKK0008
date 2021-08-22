#define Pixel
#include <cobit.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        4 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS  4 

//Create a NeoPixel light string class.
NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
  Serial.begin(9600);
  pixels.begin();                      // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50);            // Change the brightness of the light. 0-255 level
  //int brightness = getBrightness();  // Gets the brightness of the lamp. 
  //pixels.clear();                    // The memory that fills the entire Neopixel strip is 0 / black/off.
}

void loop() {
  for(int a=0; a<NUMPIXELS; a++) {      // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright white color:
    pixels.setPixelColor(a, pixels.Color(255, 255, 255));
	
	// You can also set the color using the following function.
	//pixels.setPixelColor(a, 255, 255, 255);

    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(500);      // Pause before next pass through loop
  }
  
  for(int b=0; b<NUMPIXELS; b++) {      // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright white color:
    pixels.setPixelColor(b, pixels.Color(0, 0, 0));
	
	// You can also set the color using the following function.
	//pixels.setPixelColor(b, 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(500);      // Pause before next pass through loop
  }
}
