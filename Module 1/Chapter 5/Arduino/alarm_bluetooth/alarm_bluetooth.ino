#include <SoftwareSerial.h> // serial library used for communication

SoftwareSerial burg_alarm(10, 11); // communicates via TX, RX at 10, 11 respectively
int ledPin = 13; // in built LED to show status changes
int pirPIN = 2;   // signal of the PIR sensor goes to pin 2
int pirState = LOW; // initiate the PIR status to LOW (no motion)
int pirVal = 0; // variable for storing the PIR status

void setup() {
  burg_alarm.begin(9600); // communication begins on baud 9600
  pinMode(ledPin, OUTPUT); // sets the LED pin as output
  delay(5000); // waits 5 seconds for motion to die down
}

void loop(){
  pirVal = digitalRead(pirPIN);  // read input from the sensor
  if (pirVal == HIGH) {          // if input is HIGH (motion detected)
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(150);  // small delay
    if (pirState == LOW) { // checks if the PIR state is LOW while the input is HIGH
    // this means, there wasn't motion before, but there is something happening now
      Serial.println("Motion detected!"); // prints out an Alert
      burg_alarm.println('1'); // sends out '1' for when motion is detected via Bluetooth to python
      pirState = HIGH; // sets the pirState to HIGH (motion detected)
    }
  } else { // no motion detected
      digitalWrite(ledPin, LOW); // turn LED OFF
      delay(300);  // small delay
      if (pirState == HIGH){ // if there was motion, but isn't any now
      Serial.println("Motion ended!");
      burg_alarm.println('0'); // sends a '0' when the motion has ended
      pirState = LOW; // sets the state to LOW (no motion)
    }
  }
}
