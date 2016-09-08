/*
Blink sensor code using HC-SR04

Connections (HC-SR04 >> Arduino):
VCC - 5V
Trig - 8
Echo - 7
GND - GND

Author: Adith Jagadish Boloor

Note: This code is the modified version of the
Arduino Example "Ping" sketch
*/

#define ledPin 13 // LED on 13 connected to adjacent GND
#define trigPin 8 // trigger pin from sensor goes to pin 8
#define echoPin 7 // echo pin from sensor goes to pin 7

void setup() {
  Serial.begin (9600); // Begin serial monitor on baud 9600
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
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
  if (distance < 15) {  // Threshold set to 15 cm; LED turns off if object distance < 15cms
  //if ((distance > 0) && (distance > 15)) { // Uncomment this line and comment the previous line if 0's error
    digitalWrite(ledPin,HIGH); 
}
  else {
    digitalWrite(ledPin,LOW);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Outside sensor range");
  }
  else {
    Serial.print(distance); // prints the distance on the serial monitor
    Serial.println(" cm");
  }
  delay(500); // wait time between each reading
}
