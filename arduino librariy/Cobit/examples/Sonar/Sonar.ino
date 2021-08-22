#include <cobit.h>
/*
 * The maximum measurement distance of sonar is 255CM with an accuracy of +/-1CM.
 * Designer ：jalen
 * Date：2021-6-12
 */
 
cobit Car;

/***************************************************************/
void setup(){
  Serial.begin(9600);             // start serial for output
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  //use for sonar
  Car.Sonar_On();
  delay(100);
  //Car.Sonar_Off();               //turn off sonar
}

/***************************************************************/
void loop(){
  int distance = 0;
  distance = Car.Sonar_Measurement_Distance();  //Sonar data refresh rate = 50ms
  Serial.println(distance);
  delay(1000);
}
