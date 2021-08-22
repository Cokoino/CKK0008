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
  Serial.print(Car.Battery_Voltage());
  Serial.print("V     ");
  Serial.print(Car.Battery_Level());
  Serial.println("%");
  delay(1000);
}
