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

#define BLUETOOTH
#include <cobit.h>

void setup(){                   
  Serial.begin(9600);
  BluetoothInit();  //Baud rate is 9600.
}

/////////////////////////////////////////////////////////////////////////
void loop(){
  BluetoothRead();               //read data
  if(bCMD){                      //Check whether the data is read completely.
	for(int i=0;i<bCmdNum;i++){
	Serial.println(bCmd[i]);     //Serial port monitor prints data.
	}
	bCMD = false;
  }
}


