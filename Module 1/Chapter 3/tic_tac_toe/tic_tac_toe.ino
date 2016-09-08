#include <Wire.h> // default Wire library
#include <mpr121.h> // touch pad library

int num = 0; // variable to store pressed number

void setup()
{ 
  Serial.begin(19200); // begin the Serial Port at 19200 baud
  Wire.begin(); // initiate the wire library
  CapaTouch.begin(); // inititate the capacitive touch library
  delay(500);
}

void loop()
{
  num = CapaTouch.keyPad(); // stores the pressed number to num
  if(num > 0){ // checks if the key pressed is within scope
    Serial.print(num); // prints the number to the serial port
  }
	delay(200); // small delay to allow serial communication
}
