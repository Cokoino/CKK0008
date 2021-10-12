/*
 * mobile phone communicates with Cobit
 * button format: S-0x00-data-P
 * slider format: S-0x(0a-0e)-data-P
 * accelerometer format: S-0x14-dataX-dataY-dataZ-P
 * ----data > 100 : real data = -(data-100)/10
 * ----data < 100 : real data = data/10
 * Designer ：jalen
 * Date：2021-9-6
 */
	
#ifndef BLUETOOTH_h
#define BLUETOOTH_h

#include <SoftwareSerial.h>
#define RX_      8
#define TX_      7
SoftwareSerial bluetooth(RX_, TX_);

bool bCMD = false;

enum bElement{
  /////////SensorAddress/////////
  b_Button                  =    0x00,
  b_Slide                   =    0x0A,
  b_XYZ                     =    0x14,
  
  /////////Data(master)/////////
  b_Up                      =    0x01,
  b_Left                    =    0x02,
  b_Center                  =    0x03,
  b_Right                   =    0x04,
  b_Down                    =    0x05,
  b_Add                     =    0x06,
  b_Sub                     =    0x07,
  b_Light                   =    0x08,
  b_Horn                    =    0x09,
  b_Sonar                   =    0x0A,
  b_Button1                 =    0x0B,
  b_Way                     =    0x0C,
  b_Follow                  =    0x0D,
  b_Button2                 =    0x0E,
  b_Red                     =    0x0F,
  b_Green                   =    0x10,
  b_Blue                    =    0x11,
  b_purple                  =    0x12,
  b_Exchange                =    0x13,
  b_Seagreen                =    0x14,  
  b_Yellow                  =    0x15, 
  b_Grey                    =    0x16,      
  b_DarkPurple              =    0x17,   
  b_Do                      =    0x18,   
  b_Re                      =    0x19, 
  b_Mi                      =    0x1A, 
  b_Fa                      =    0x1B,   
  b_Sol                     =    0x1C, 
  b_La                      =    0x1D, 
  b_Ti                      =    0x1E, 
};

#define bCmdNum  4
String bString  = ""; 
unsigned int bCmd[bCmdNum] = {0,0,0,0};

///////////////////////////////////////////////////////////////////
//  Converts strings to numbers.
void strToNum(String str){
	int NumData = str.length()/3;
	for(int i=0; i<NumData; i++){
		bCmd[i]= str.substring(i*3,i*3+3).toInt();
	}
}

///////////////////////////////////////////////////////////////////
void BluetoothInit(void){
  bluetooth.begin(9600);
  // reserve 100 bytes for the inputString:
}

///////////////////////////////////////////////////////////////////
void BluetoothRead() {
  while (bluetooth.available()) {
	if(!bCMD){
		for(int i=0; i<bCmdNum; i++){
			bCmd[i]=0;
		}
	}
	char inChar = bluetooth.read();
	bString += inChar;
	if(inChar == 'P'){
		if(bString[0]=='S'){
			//Remove the characters 'S' and 'P', and then convert the string to a number.
			strToNum(bString.substring(1, bString.length()-1));  
			bCMD = true;
		}
	// clear the string:
	bString = "";
	}
  }
}

#endif



