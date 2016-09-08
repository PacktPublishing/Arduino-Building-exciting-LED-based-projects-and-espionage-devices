/*
  Double Blink
  Turns on and off two LEDs alternatively for one second each repeatedly.

  This example code is in the public domain.
*/

int led1 = 12;
int led2 = 13;

void setup() {
  // initialize the digital pins as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  // turn off LEDs before loop begins
  digitalWrite(led1, LOW);   // turn the LED off (LOW is the voltage level)
  digitalWrite(led2, LOW);   // turn the LED off (LOW is the voltage level)
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, LOW);    // turn the LED off (LOW is the voltage level)
  delay(1000);                // wait for a second
  digitalWrite(led1, LOW);    // turn the LED off (LOW is the voltage level)
  digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
}
