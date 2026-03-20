/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
#include <Arduino.h>
const int FLEX_PIN =2; // Pin connected to voltage divider output
const int BUT_PIN = 4;
void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
}

void loop() 
{

  //The sensor exponetinly goes up so make a function that can turn it liner
  // The flex sensor is wired to pin d2
  // The force sensor is wired to pin d4
  Serial.println("ready for typing");
  Serial.println("ready for typing");
  while(1){
    float but=analogRead(BUT_PIN)/100.0;
    // Serial.println(but);
    if (but>15){
      Serial.print("Button: ");
      float flex=analogRead(FLEX_PIN)/100.0;
      if (flex>29.8){ 
        // Use the calculated resistance to estimate the sensor's
        // bend angle:
        Serial.print("M  ");
        Serial.print(flex);
        Serial.print("  Pressure  ");
        Serial.println(but);
      }
      else if (flex>18){
        Serial.print("J  ");
        Serial.print(flex);
        Serial.print("  Pressure  ");
        Serial.println(but);
      }
      else if (flex>=0){
        Serial.print("U  ");
        Serial.print(flex);
        Serial.print("  Pressure  ");
        Serial.println(but);
      }
      else{
        Serial.println("Error!");
      }
      while (but>10){ but=analogRead(BUT_PIN)/100.0;}
    }
    
  }
}
