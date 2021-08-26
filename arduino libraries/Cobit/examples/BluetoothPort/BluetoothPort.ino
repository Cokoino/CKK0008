#define BLUETOOTH
#include <cobit.h>

void setup(){                   
  Serial.begin(9600);
  BluetoothPort.begin(115200);
}

/////////////////////////////////////////////////////////////////////////
void loop() {
  if (BluetoothPort.available()) {
	Serial.println(BluetoothPort.read());
  }
}


