int redLed = 11;
int blueLed = 10;
int greenLed = 9;

void setup()
{
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop()
{
  setColor(255, 0, 0); // Red
  delay(500);
  setColor(255, 0, 255); // Magenta
  delay(500);
  setColor(0, 0, 255); // Blue
  delay(500);
  setColor(0, 255, 255); // Cyan
  delay(500);
  setColor(0, 255, 0); // Green
  delay(500);
  setColor(255, 255, 0); // Yellow
  delay(500);
  setColor(255, 255, 255); // White
  delay(500);
}

void setColor(int red, int green, int blue)
{
  // For common anode LED, we need to substract value from 255.
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(redLed, red);
  analogWrite(greenLed, green);
  analogWrite(blueLed, blue);
}
