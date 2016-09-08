void setup()
{
  DDRD = B11111111; // set PORTD (digital 7-0) to outputs
}

void loop()
{
  PORTD = B11110000; // digital 4~7 HIGH, digital 3-0 LOW
  delay(2000);
  PORTD = B00001111; // digital 4~7 LOW, digital 3-0 HIGH
  delay(2000);
}

