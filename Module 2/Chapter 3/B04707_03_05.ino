#include <IRremote.h>
const int IR_RECEIVER = 11; // Connect output pin of TSOP38238 to pin 11
IRrecv receiver(IR_RECEIVER);
decode_results buttonPressed;
long int buttonValue = 0;

// Mention the codes, you get from previous exercise
const long int POWER_BUTTON = 54572; // Power button to turn on or off the backlight
const long int PLUS_BUTTON = 54536;  // Increase brightness of the LED Strip
const long int MINUS_BUTTON = 54608; // Decrease brightness of the LED strip
const long int CHANGE_COLOR = 54584; // Decrease brightness of the LED strip

const int FADE_AMOUNT = 5; // For fast increasing/decreasing brightness increase this value
boolean isOn = false;

int redLed = 5;
int greenLed = 6;
int blueLed = 3;

int redValue   = 0;
int greenValue = 0;
int blueValue  = 0;

int colors[3];

// Power up the LED strip with random color
void powerUp(int *colors)
{
  redValue = random(0, 256); // Randomly generate 1 to 255
  greenValue = random(0, 256); // Randomly generate 1 to 255
  blueValue = random(0, 256); // Randomly generate 1 to 255

  analogWrite(redLed, redValue);
  analogWrite(greenLed, greenValue);
  analogWrite(blueLed, blueValue);

  colors[0] = redValue;
  colors[1] = greenValue;
  colors[2] = blueValue;
}

// Turn off the LED
void powerDown(int *colors)
{
  redValue = colors[0];
  greenValue = colors[1];
  blueValue = colors[2];

  //Decrementing all the values one by one for turning off all the LEDs.
  for (; redValue > 0; redValue--) {
    analogWrite(redLed, redValue);
    delay(10);
  }
  for (; greenValue > 0; greenValue--) {
    analogWrite(greenLed, greenValue);
    delay(10);
  }
  for (; blueValue > 0; blueValue--) {
    analogWrite(blueLed, blueValue);
    delay(10);
  }
  colors[0] = redValue;
  colors[1] = greenValue;
  colors[2] = blueValue;
}

void increaseBrightness(int *colors)
{
  redValue = colors[0];
  greenValue = colors[1];
  blueValue = colors[2];

  redValue += FADE_AMOUNT;
  greenValue += FADE_AMOUNT;
  blueValue += FADE_AMOUNT;

  if (redValue >= 255) {
    redValue = 255;
  }

  if (greenValue >= 255) {
    greenValue = 255;
  }

  if (blueValue >= 255) {
    blueValue = 255;
  }
  analogWrite(redLed, redValue);
  analogWrite(greenLed, greenValue);
  analogWrite(blueLed, blueValue);

  colors[0] = redValue;
  colors[1] = greenValue;
  colors[2] = blueValue;
}

void decreaseBrightness(int *colors)
{
  redValue = colors[0];
  greenValue = colors[1];

  blueValue = colors[2];

  redValue -= FADE_AMOUNT;
  greenValue -= FADE_AMOUNT;
  blueValue -= FADE_AMOUNT;

  if (redValue <= 5) {
    redValue = 0;
  }

  if (greenValue <= 5) {
    greenValue = 0;
  }

  if (blueValue <= 5) {
    blueValue = 0;
  }
  analogWrite(redLed, redValue);
  analogWrite(greenLed, greenValue);
  analogWrite(blueLed, blueValue);

  colors[0] = redValue;
  colors[1] = greenValue;
  colors[2] = blueValue;
}

// Randomly generates a color and make a smooth transition to that color
void changeColor(int *colors)
{
  int newRedValue = random(0, 256); // Randomly generate 1 to 255
  int newGreenValue = random(0, 256); // Randomly generate 1 to 255
  int newBlueValue = random(0, 256); // Randomly generate 1 to 255

  redValue = colors[0];
  greenValue = colors[1];
  blueValue = colors[2];

  if (newRedValue > redValue) {
    for (; redValue >= newRedValue; redValue++) {
      analogWrite(redLed, redValue);
      delay(10);
    }
  }
  else {
    for (; redValue <= newRedValue; redValue--) {
      analogWrite(redLed, redValue);
      delay(10);
    }
  }

  if (newGreenValue > greenValue) {
    for (; greenValue >= newGreenValue; greenValue++) {
      analogWrite(greenLed, greenValue);
      delay(10);
    }
  }
  else {
    for (; greenValue <= newGreenValue; greenValue--) {
      analogWrite(greenLed, greenValue);
      delay(10);
    }
  }

  if (newBlueValue > blueValue) {
    for (; blueValue >= newBlueValue; blueValue++) {
      analogWrite(blueLed, blueValue);
      delay(10);
    }
  }
  else {
    for (; blueValue <= newBlueValue; blueValue--) {
      analogWrite(blueLed, blueValue);
      delay(10);
    }
  }

  colors[0] = redValue;
  colors[1] = greenValue;
  colors[2] = blueValue;
}

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn(); // Start the receiver

  randomSeed(analogRead(0));

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {

  if (receiver.decode(&buttonPressed))
  {
    buttonValue = buttonPressed.value;
    Serial.println(buttonValue);
    switch (buttonValue) {
      case POWER_BUTTON:
        if (!isOn) {
          powerUp(colors);
          isOn = true;
        }
        else {
          powerDown(colors);
          isOn = false;
        }
        break;
      case PLUS_BUTTON:
        decreaseBrightness(colors);
        break;
      case MINUS_BUTTON:
        increaseBrightness(colors);
        break;
      case CHANGE_COLOR:
        changeColor(colors);
        break;
      default:
        Serial.println("Waiting for input. ");
    }
    receiver.resume(); // Receive the next value
  }
  delay(100);
}

