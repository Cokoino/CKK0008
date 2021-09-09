#include <cobit.h>
/*
 * Buzzer can be set frequency range: 20-- 1K Hz, volume: 0-9 level
 * Designer ：jalen
 * Date：2021-6-12
 */
cobit Car;

/***************************************************************/
void setup(){
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  
  Car.Buzzer_On();
  Car.Buzzer_Frequency(100);     // frequency = 20-1K
  Car.Buzzer_Volume(5);          // Set the volume of buzzer, level:0--9
  //Car.Buzzer_Off();            //turn off buzzer
}

/***************************************************************/
void loop(){
  for(int Frequency = 20; Frequency <= 1000; Frequency ++){
  Car.Buzzer_Frequency(Frequency);
  delay(50);
  }
}
