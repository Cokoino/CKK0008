/*
 * wheels diameter is 65mm，Minimum rotation Angle is 0.9 degrees.
 * Speed rating：0 = 0rpm，1 = 15rpm，2 = 30rpm，3 = 60rpm，4 = 120rpm
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Buzzer can be set frequency range: 20-- 1K Hz, volume: 0-5 level
 * Designer ：jalen
 * Date：2021-6-27
 *
 * Microbit communicates with Cobit
 * Write: S + SensorAddress + Data + ... + P --> Waiting to receive data --> SP
 * Read : S + SensorAddress + Data + ... + P --> Waiting to receive data --> S + Data + P
 */
	
#ifndef MICROBIT_h
#define MICROBIT_h

#include <SoftwareSerial.h>
#define RX      8
#define TX      7
SoftwareSerial microbit(RX, TX);

enum mElement{
  /////////SensorAddress/////////
  LeftWheel               =    0x64,
  RightWheel              =    0x65,
  Sonar                   =    0x66,
  Buzzer                  =    0x67,
  Servo                   =    0x68,
  Reset                   =    0x69,
  LeftHeadlight           =    0x6A,
  RightHeadlight          =    0x6B,
  LeftPR                  =    0x6C,
  RightPR                 =    0x6D,
  LeftLineDetection       =    0x6E,
  RightLineDetection      =    0x6F,
  RGB_                    =    0x70,
  Voltmeter               =    0x71,
  a0                      =    0x72,
  a1                      =    0x73,
  a2                      =    0x74,
  d11                     =    0x75,
  d12                     =    0x76,
  d13                     =    0x77,
  Car_                    =    0x78,
  Font                    =    0x79,
  IRremote                =    0x7A,
  
  /////////Data(master)/////////
  CW                      =    0x65,
  CCW                     =    0x66,
  On                      =    0x67,
  Off                     =    0x68,
  Step                    =    0x69,
  Continue                =    0x6A,
  Distance                =    0x6B,
  Stop                    =    0x6C,
  Brake                   =    0x6D,
  Forward                 =    0x6E,
  Back                    =    0x6F,
  Left                    =    0x70,
  Right                   =    0x71,
  ForwardDistance         =    0x72,
  BackDistance            =    0x73,
  Speed                   =    0x74,
  TurnDegree              =    0x75,
  Frequency               =    0x76,
  Volume                  =    0x77,
  Servo1                  =    0x78,  
  Servo2                  =    0x79, 
  Servo3                  =    0x7A,      
  RGB1                    =    0x7B,   
  RGB2                    =    0x7C,    
  RGB3          		  =    0x7D,
  RGB4                    =    0x7E,
  Brightness         	  =    0x7F,  
  Read              	  =    0x80,
  Write            		  =    0x81,
  Digital          		  =    0x82,
  Analog          		  =    0x83,
  Percent                 =    0x84,
  Input                   =    0x85,
  Output                  =    0x86,
};

String inputString  = "";          // a String to hold incoming data
bool cmdComplete    = false;

String fontString   = "";

#define cmdNum  5
unsigned int cmd[cmdNum] = {0,0,0,0,0};

///////////////////////////////////////////////////////////////////
void mSerialInit(void){
  microbit.begin(115200);
  // reserve 100 bytes for the inputString:
  inputString.reserve(100);
  fontString.reserve(100);
}

///////////////////////////////////////////////////////////////////
//  Converts strings to numbers.
void StrToNum(String str){
	int NumData = str.length()/3;
	for(int i=0; i<NumData; i++){
		cmd[i]= str.substring(i*3,i*3+3).toInt();
	}
}

///////////////////////////////////////////////////////////////////
//  Converts numbers to strings. num = 0-999
char * NumToChar(int num){
	char *str = "   ";
	str[0] = (char)(num/100+48);
	str[1] = (char)(num%100/10+48);
	str[2] = (char)(num%10+48);
	return str;
}

///////////////////////////////////////////////////////////////////
void mSerialRead() {
  while (microbit.available()) {
    // get the new byte:
    char inChar = (char)microbit.read();
    // add it to the inputString:
    inputString += inChar;
    if(inChar == 'P'){
		if (inputString[0] == 'S') {
	  	    #ifdef TEST                     // For testing code.
		    Serial.println(inputString);    // start serial for output
		    #endif
			//Remove the characters 'S' and 'P', and then convert the string to a number.
			StrToNum(inputString.substring(1, inputString.length()-1));  
		    cmdComplete = true;
	    }
	// clear the string:
	inputString = "";
    }
  }
}

///////////////////////////////////////////////////////////////////
void mSerialSend(int data){ 
	microbit.write('S');
	microbit.write(NumToChar(data));
	microbit.write('P');
	
	#ifdef TEST 
	Serial.println(NumToChar(data));
	#endif
}

///////////////////////////////////////////////////////////////////
void mSerialACK(void){ 
	microbit.write('S');
	microbit.write('P');
	
	#ifdef TEST                     // For testing code.
    Serial.println("ACK OK!");        // start serial for output
    #endif
}

#endif



