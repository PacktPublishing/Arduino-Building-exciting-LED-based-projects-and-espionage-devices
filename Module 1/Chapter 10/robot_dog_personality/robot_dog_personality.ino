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
#include <NewPing.h>

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

# define tail_pin 34

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

#define tail_center       1400

#define TRIGGER_PIN  12  // Trig -> D12
#define ECHO_PIN     11  // Echo -> D11
#define MAX_DISTANCE 30 // Max Dist

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

Servo tail_servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int LH_time = 400; // Lower Hip Lift time 
int K_time = 300;  // Knee Lift time
int delay_time = 200; // time between actions
int disturb_status = 0; // initate disturb status
int const_ctr = 0;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
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
  tail_servo.attach(tail_pin);
  
  sit();
  delay(2000);
}

void loop()  {
  if(disturb_status == 0)
  {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  if(uS !=0)
  {
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
    int obj_dist = uS / US_ROUNDTRIP_CM;
    if(obj_dist < 30) // minimum distance of 30 cms to be disturbed
    {
      Serial.println("DISTRUBED!");
      disturb_status = 1;
      Serial.print("Disturb status: ");
      Serial.println(disturb_status);
    }
  }
  }
  else if(disturb_status == 1)
  {
    for(int i = 0; i <3; i++)
    {
      tail_servo.writeMicroseconds(tail_center-300);
      delay(150);
      tail_servo.writeMicroseconds(tail_center+300);
      delay(150);
    }
    
  center_servos();
    delay(1000);    
    for(int i = 0; i <3; i++)
    {
      tail_servo.writeMicroseconds(tail_center-300);
      delay(150);
      tail_servo.writeMicroseconds(tail_center+300);
      delay(150);
    }
    tail_servo.writeMicroseconds(tail_center);
    delay(200);
    disturb_status = 2;
  }
  if(disturb_status == 2)
  {
    unsigned int uS = sonar.ping();
    if(uS !=0)
    {
      int obj_dist = uS / US_ROUNDTRIP_CM;
      int old_obj_dist = obj_dist;
      delay(100);
      const_ctr++;
      if(obj_dist < 10)
      {
        hand_shake();
        disturb_status = 0;
      }
      else if(obj_dist > 20)
      {
        walk();
        center_servos();
      }
      if(const_ctr > 30)
      {
        sit();
        disturb_status = 0;
      }
    }
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
  
void walk()
{
  for(int j = 0; j< 2; j++)
  {
    
    F_R_LH_servo.writeMicroseconds(F_R_LH_center-LH_time);  
    F_R_K_servo.writeMicroseconds(F_R_K_center-K_time); 
    B_R_LH_servo.writeMicroseconds(B_R_LH_center);  
    B_R_K_servo.writeMicroseconds(B_R_K_center); 
    B_L_LH_servo.writeMicroseconds(B_L_LH_center);  
    B_L_K_servo.writeMicroseconds(B_L_K_center);  
    F_L_LH_servo.writeMicroseconds(F_L_LH_center);  
    F_L_K_servo.writeMicroseconds(F_L_K_center); 
    delay(delay_time);
    B_L_LH_servo.writeMicroseconds(B_L_LH_center+LH_time);  
    B_L_K_servo.writeMicroseconds(B_L_K_center+K_time);
    delay(delay_time);
    F_R_LH_servo.writeMicroseconds(F_R_LH_center);  
    F_R_K_servo.writeMicroseconds(F_R_K_center);
    F_L_LH_servo.writeMicroseconds(F_L_LH_center+LH_time);  
    F_L_K_servo.writeMicroseconds(F_L_K_center+K_time);
    B_R_LH_servo.writeMicroseconds(B_R_LH_center);  
    B_R_K_servo.writeMicroseconds(B_R_K_center); 
    B_L_LH_servo.writeMicroseconds(B_L_LH_center);  
    B_L_K_servo.writeMicroseconds(B_L_K_center);   
    delay(delay_time); 
    B_R_LH_servo.writeMicroseconds(B_R_LH_center-LH_time);  
    B_R_K_servo.writeMicroseconds(B_R_K_center-K_time); 
    delay(delay_time);
  }
  delay(1000);
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
