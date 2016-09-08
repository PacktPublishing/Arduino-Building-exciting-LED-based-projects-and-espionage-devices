// Multi-Sweep by Adith Jagadish Boloor
// This is modified version of the sweep program by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;  
Servo myservo9;
Servo myservo10;
Servo myservo11;  
Servo myservo12;

int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  // declaring the servos with respect to their digital pin connections
  myservo1.attach(22);
  myservo2.attach(23);
  myservo3.attach(24); 
  myservo4.attach(25);
  myservo5.attach(26); 
  myservo6.attach(27);
  myservo7.attach(28);
  myservo8.attach(29);
  myservo9.attach(30);
  myservo10.attach(31);
  myservo11.attach(32);
  myservo12.attach(33);
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);             // tell servo to go to position in variable 'pos' 
    myservo2.write(pos);              
    myservo3.write(pos);              
    myservo4.write(pos);
    myservo5.write(pos); 
    myservo6.write(pos); 
    myservo7.write(pos);      
    myservo8.write(pos);                       
    myservo9.write(pos); 
    myservo10.write(pos);
    myservo11.write(pos); 
    myservo12.write(pos);
    delay(15);                         // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(pos);             // tell servo to go to position in variable 'pos' 
    myservo2.write(pos);              
    myservo3.write(pos);              
    myservo4.write(pos);
    myservo5.write(pos); 
    myservo6.write(pos); 
    myservo7.write(pos);      
    myservo8.write(pos);                       
    myservo9.write(pos); 
    myservo10.write(pos);
    myservo11.write(pos); 
    myservo12.write(pos);
    delay(15);                         // waits 15ms for the servo to reach the position 
  } 
} 
