#include <cobit.h>

cobit Car;

void setup(){  
  Serial.begin(9600);
  Car.Reset_chip();               //Reset N76E003. This function must be used once within the setup function.
  delay(100);
  Car.Pen(true);                  
  Car.Pen_Rise();                 
  Car.FontSize(1);                //Set the font size = 1-9;
}

/***************************************************************/
void loop() {
  Car.writing(1, "123ABCabc");   //The first parameter is the speed(0-4) and the second is the string.
  delay(3000);
}

/***************************************************************/


