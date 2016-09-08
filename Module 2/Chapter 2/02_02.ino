int led = 11;           // the pin that the LED is attached to
int brightness = 0;     // how bright the LED is
int steps = 5;          // how many points to fade the LED by

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  // Setting brightness of LED:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + steps;

  // When brightness value reaches either 0 or 255, reverse direction of fading
  if (brightness == 0 || brightness == 255) {
    steps = -steps ;
  }
  
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
