// Connections: 
// SDA (MPR121) -> PIN A4 (Arduino)
// SCL (MPR121) -> PIN A5 (Arduino)
// IRQ (MPR121) -> PIN A2 (Arduino) 

// Libraries
#include <Wire.h>
#include <mpr121.h> // Touch Pad library

int X ;  // X-coordinate
int Y ;  // Y-coordinate
int inByte = 0; // incoming serial byte

void setup()
{ 
  Serial.begin(57600); // Begin serial at 57600 baud rate (faster)
  Wire.begin(); // intiialize wire library
  CapaTouch.begin(); // initialize the capacitive touch library
  delay(500); // brief delay for initialization
}

void loop()
{   
  X = CapaTouch.getX(); // Get X position.
  Y = CapaTouch.getY(); // Get Y position.
  
  // Determine whether in the range.If not,do nothing.
  if(X>=1&&X<=9&&Y>=1&&Y<=13)
  {
    // Debug lines, can be uncommented to check inputs
    //Serial.print("X=");
    //Serial.write(X);
    //Serial.print("  Y=");
    //Serial.write(Y); 
    
    // convert X and Y coordinates into one variable
    if(Y<10)
    {
      Serial.print(X*10+Y); // prints to serial port
    }
    else if(Y>9)
    {
      Serial.print(X*100+Y); // prints to serial port
    }
   }
     delay(200); // delay for message to be relayed
}








