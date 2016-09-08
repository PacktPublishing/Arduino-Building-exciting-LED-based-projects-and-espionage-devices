/*
// Defining servo pins
F_R_UH - Front Right Upper Hip
F_R_LH - Front Right Lower Hip 
F_R_K - Front Right Knee

F_L_UH - Front Left Upper Hip
F_L_LH - Front Left Lower Hip 
F_L_K_ - Front Left Knee 

B_R_UH - Back Right Upper Hip 
B_R_LH - Back Right Lower Hip 
B_R_K - Back Right Knee 

B_L_UH - Back Left Upper Hip   
B_L_LH - Back Left Lower Hip  
B_L_K - Back Left Knee  
*/

// Initialize Servo Libraries
#include <Servo.h>

// Defining servo pins
#define F_R_UH_pin 22 
#define F_R_LH_pin 23  
#define F_R_K_pin  24

#define F_L_UH_pin 25
#define F_L_LH_pin 26
#define F_L_K_pin  27

#define B_R_UH_pin 28
#define B_R_LH_pin 29
#define B_R_K_pin  30

#define B_L_UH_pin 31
#define B_L_LH_pin 32
#define B_L_K_pin  33

// Declare starting positions of servos
#define F_R_UH_center      1250
#define F_R_LH_center      1200
#define F_R_K_center       1500

#define F_L_UH_center      1850
#define F_L_LH_center      1550
#define F_L_K_center       1400

#define B_R_UH_center      1600
#define B_R_LH_center      1550
#define B_R_K_center       1500

#define B_L_UH_center      1050
#define B_L_LH_center      1400
#define B_L_K_center       1500

// Define servos
Servo F_R_UH_servo;                                               
Servo F_R_LH_servo;
Servo F_R_K_servo;

Servo F_L_UH_servo;                                               
Servo F_L_LH_servo;
Servo F_L_K_servo;

Servo B_R_UH_servo;                                               
Servo B_R_LH_servo;
Servo B_R_K_servo;

Servo B_L_UH_servo;                                               
Servo B_L_LH_servo;
Servo B_L_K_servo;

// Buffer for the speech message
char INBYTE;

void setup()
{
    // Attach servos
  F_R_UH_servo.attach(F_R_UH_pin); 
  F_R_LH_servo.attach(F_R_LH_pin);  
  F_R_K_servo.attach(F_R_K_pin);  
  F_L_UH_servo.attach(F_L_UH_pin);  
  F_L_LH_servo.attach(F_L_LH_pin);  
  F_L_K_servo.attach(F_L_K_pin);  
  B_R_UH_servo.attach(B_R_UH_pin); 
  B_R_LH_servo.attach(B_R_LH_pin);  
  B_R_K_servo.attach(B_R_K_pin);  
  B_L_UH_servo.attach(B_L_UH_pin);  
  B_L_LH_servo.attach(B_L_LH_pin);  
  B_L_K_servo.attach(B_L_K_pin);
  
  // Center servos
  F_R_UH_servo.writeMicroseconds(F_R_UH_center);
  F_R_LH_servo.writeMicroseconds(F_R_LH_center);  
  F_R_K_servo.writeMicroseconds(F_R_K_center); 
  F_L_UH_servo.writeMicroseconds(F_L_UH_center);  
  F_L_LH_servo.writeMicroseconds(F_L_LH_center);  
  F_L_K_servo.writeMicroseconds(F_L_K_center);  
  B_R_UH_servo.writeMicroseconds(B_R_UH_center);
  B_R_LH_servo.writeMicroseconds(B_R_LH_center);  
  B_R_K_servo.writeMicroseconds(B_R_K_center);  
  B_L_UH_servo.writeMicroseconds(B_L_UH_center);  
  B_L_LH_servo.writeMicroseconds(B_L_LH_center);  
  B_L_K_servo.writeMicroseconds(B_L_K_center);  
  tail_servo.writeMicroseconds(tail_center);
  delay(2000);  
}

void loop() {
  while (!Serial.available());   // stay here so long as COM port is empty   
  INBYTE = Serial.read();        // read next available byte
  delay(50);
  
  if (INBYTE == '1') // stand up
  {
    center_servos();
    delay(2000);
  }
  else if(INBYTE == '2') // sit down
  {
    sit();
    delay(2000);
  }
  else if(INBYTE == '3') // shake hands
  {
    hand_shake();
    delay(2000);
  }
}
  
void hand_shake()
{
    B_L_LH_servo.writeMicroseconds(B_L_LH_center-400);  
    B_L_K_servo.writeMicroseconds(B_L_K_center-300);
    
  delay(2000);
  F_R_LH_servo.writeMicroseconds(F_R_LH_center-600);  
    F_R_K_servo.writeMicroseconds(F_R_K_center-500);
    B_L_K_servo.writeMicroseconds(B_L_K_center);
    delay(2000);
    for(int i = 0; i < 4; i++)
    {F_R_K_servo.writeMicroseconds(F_R_K_center-200);
    delay(200);
    F_R_K_servo.writeMicroseconds(F_R_K_center+300);
    delay(200);
    
    }
    delay(2000);
    
  F_R_UH_servo.writeMicroseconds(F_R_UH_center);
  F_R_LH_servo.writeMicroseconds(F_R_LH_center-500);  
  F_R_K_servo.writeMicroseconds(F_R_K_center-600); 
  F_L_UH_servo.writeMicroseconds(F_L_UH_center);  
  F_L_LH_servo.writeMicroseconds(F_L_LH_center+500);  
  F_L_K_servo.writeMicroseconds(F_L_K_center+600);  
  B_R_UH_servo.writeMicroseconds(B_R_UH_center);
  B_R_LH_servo.writeMicroseconds(B_R_LH_center-400);  
  B_R_K_servo.writeMicroseconds(B_R_K_center-600);  
  B_L_UH_servo.writeMicroseconds(B_L_UH_center);  
  B_L_LH_servo.writeMicroseconds(B_L_LH_center+400);  
  B_L_K_servo.writeMicroseconds(B_L_K_center+600);  
  tail_servo.writeMicroseconds(tail_center); 
  delay(2000);
}
  
void sit()
{
  // Sittng Position
  F_R_UH_servo.writeMicroseconds(F_R_UH_center);
  F_R_LH_servo.writeMicroseconds(F_R_LH_center-500);  
  F_R_K_servo.writeMicroseconds(F_R_K_center-600); 
  F_L_UH_servo.writeMicroseconds(F_L_UH_center);  
  F_L_LH_servo.writeMicroseconds(F_L_LH_center+500);  
  F_L_K_servo.writeMicroseconds(F_L_K_center+600);  
  B_R_UH_servo.writeMicroseconds(B_R_UH_center);
  B_R_LH_servo.writeMicroseconds(B_R_LH_center-300);  
  B_R_K_servo.writeMicroseconds(B_R_K_center-300);  
  B_L_UH_servo.writeMicroseconds(B_L_UH_center);  
  B_L_LH_servo.writeMicroseconds(B_L_LH_center+300);  
  B_L_K_servo.writeMicroseconds(B_L_K_center+300);  
  tail_servo.writeMicroseconds(tail_center); 
  delay(2000);
}

void center_servos()
{
  // Center servos
  F_R_UH_servo.writeMicroseconds(F_R_UH_center);
  F_R_LH_servo.writeMicroseconds(F_R_LH_center);  
  F_R_K_servo.writeMicroseconds(F_R_K_center); 
  F_L_UH_servo.writeMicroseconds(F_L_UH_center);  
  F_L_LH_servo.writeMicroseconds(F_L_LH_center);  
  F_L_K_servo.writeMicroseconds(F_L_K_center);  
  B_R_UH_servo.writeMicroseconds(B_R_UH_center);
  B_R_LH_servo.writeMicroseconds(B_R_LH_center);  
  B_R_K_servo.writeMicroseconds(B_R_K_center);  
  B_L_UH_servo.writeMicroseconds(B_L_UH_center);  
  B_L_LH_servo.writeMicroseconds(B_L_LH_center);  
  B_L_K_servo.writeMicroseconds(B_L_K_center);  
  tail_servo.writeMicroseconds(tail_center);
  delay(2000);
}
