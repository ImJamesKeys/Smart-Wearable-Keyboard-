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
const int BUT_PIN = 32;
int hey=0;
float smoothed=0;
float alpha=.003;
void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
float raw=analogRead(BUT_PIN);
smoothed = alpha * raw + (1 - alpha) * smoothed;
Serial.println(raw);
       
    
  
}
