#include <cobit.h>
/*
 * Designer ：jalen
 * Date：2021-6-12
 */
 
cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);
  Car.Reset_chip();                 // Reset N76E003. This function must be used once within the setup function.
  delay(100);
}

/***************************************************************/
void loop(){
  Serial.print(Car.Battery_Voltage());    //Prints the battery voltage to the serial port monitor.
  Serial.print("V     ");
  Serial.print(Car.Battery_Level());      //Print the battery voltage percentage to the serial port monitor.
  Serial.println("%");
  delay(1000);
}
