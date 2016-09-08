int redLed = 5;
int greenLed = 6;
int blueLed = 3;

int redValue   = 0;
int greenValue = 0;
int blueValue  = 0;

void setup() {
  randomSeed(analogRead(0));
}

void loop() {
  redValue = random(0, 256); // Randomly generate 1 to 255
  greenValue = random(0, 256); // Randomly generate 1 to 255
  blueValue = random(0, 256); // Randomly generate 1 to 255

  analogWrite(redLed, redValue);
  analogWrite(greenLed, greenValue);
  analogWrite(blueLed, blueValue);

  // Incrementing all the values one by one after setting the random values.
  for (redValue = 0; redValue < 255; redValue++) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }
  for (greenValue = 0; greenValue < 255; greenValue++) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }
  for (blueValue = 0; blueValue < 255; blueValue++) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }

  //Decrementing all the values one by one for turning off all the LEDs.
  for (redValue = 255; redValue > 0; redValue--) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }
  for (greenValue = 255; greenValue > 0; greenValue--) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }
  for (blueValue = 255; blueValue > 0; blueValue--) {
    analogWrite(redLed, redValue);
    analogWrite(greenLed, greenValue);
    analogWrite(blueLed, blueValue);
    delay(10);
  }
}

