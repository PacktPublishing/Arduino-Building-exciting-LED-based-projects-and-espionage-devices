#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
#define trigPin 8 // trigger pin from sensor goes to pin 8
#define echoPin 7 // echo pin from sensor goes to pin 7

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init(); // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Sensor Distance:");
  lcd.setCursor(0,1);
}

void loop()
{
  long duration, distance;

  // Send ultrasonic wave
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Receive echo
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58 ; // Convert duration to distance (cm) use 148 for inches

  if (distance >= 200 || distance <= 0){
    lcd.setCursor(0,1);
    lcd.print("Outside range! ");
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("               ");
    lcd.setCursor(2,1);
    lcd.print(distance); // prints the distance on the lcd in cm
    lcd.print(" cm ");  
    lcd.print(distance*58/148); // prints the distance in inches
    lcd.print(" in");
}
  delay(500); // wait time between each reading

}
