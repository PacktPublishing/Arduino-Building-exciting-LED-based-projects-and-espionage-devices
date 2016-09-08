int LEDPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int noOfLEDs = 8;

//data corresponding to the each alphabet and a few characters to be displayed
byte H[] = {B11111111, B11111111, B00011000, B00011000, B00011000, B00011000, B11111111, B11111111};
byte E[] = {B00000000, B11111111, B11011011, B11011011, B11011011, B11011011, B11000011, B11000011};
byte L[] = {B00000000, B11111111, B11111111, B00000011, B00000011, B00000011, B00000011, B00000011};
byte O[] = {B00000000, B11111111, B11111111, B11000011, B11000011, B11000011, B11111111, B11111111};
byte fullstop[] = {B00000000, B00000000, B00000000, B00000011, B00000011, B00000000, B00000000, B00000000};
byte comma[] = {B00000000, B00000000, B00000000, B00000110, B00000101, B00000000, B00000000, B00000000};

// Customize parameters based on the need
int timeBetweenColumn = 2.2;
int timeBtwnFrame = 20;
int frame_len = 8;

void setup()
{
  int i;
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);
  for (i = 0; i < noOfLEDs; i++) {
    pinMode(LEDPins[i], OUTPUT);  // set each pin as an output
  }
}

void loop()
{
  int b = 0;
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  delay(timeBtwnFrame);
  show(H);
  delay(timeBtwnFrame);
  show(E);
  delay(timeBtwnFrame);
  show(L);
  delay(timeBtwnFrame);
  show(L);
  delay(timeBtwnFrame);
  show(O);
  delay(timeBtwnFrame);
}

void show( byte* image )
{
  int a, b, c;

  // go through all data for all columns in each frame.
  for (b = 0; b < frame_len; b++)
  {
    for (c = 0; c < noOfLEDs; c++)
    {
      digitalWrite(LEDPins[c], bitRead(image[b], c));
    }
    delay(timeBetweenColumn);
  }
  for (c = 0; c < noOfLEDs; c++)
  {
    digitalWrite(LEDPins[c], LOW);
  }
}

