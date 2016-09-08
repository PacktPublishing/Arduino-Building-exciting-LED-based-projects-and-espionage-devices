#include <fix_fft.h>

int LEDPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
int x = 0;
char imaginary[128], inputSignal[128];
char outputAverage[14];
int i = 0, inputValue;
#define AUDIOPIN 1

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  for (i = 0; i < 128; i++) {
    inputValue = analogRead(AUDIOPIN);
    inputSignal[i] = inputValue;
    imaginary[i] = 0;
  };
  fix_fft(inputSignal, imaginary, 7, 0);
  for (i = 0; i < 64; i++) {
    inputSignal[i] = sqrt(inputSignal[i] * inputSignal[i] + imaginary[i] * imaginary[i]);  // this gets the absolute value of the values in the
    //array, so we're only dealing with positive numbers
  };

  // average bars together
  for (i = 0; i < 14; i++) {
    outputAverage[i] = inputSignal[i * 4] + inputSignal[i * 4 + 1] + inputSignal[i * 4 + 2] + inputSignal[i * 4 + 3]; // average together
    outputAverage[i] = map(outputAverage[i], 0, 30, 0, 9);
  }
  int value = outputAverage[0];//0 for bass
  writetoLED(value);
}

void writetoLED(int mappedSignal)
{
  if (mappedSignal > 8)
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
  }
  else if (mappedSignal > 7)
  {
    for (int i = 0; i < 7; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 7; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 6)
  {
    for (int i = 0; i < 6; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 6; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 5)
  {
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 5; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 4)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 4; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 3)
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 3; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 2)
  {
    for (int i = 0; i < 2; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 2; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else if (mappedSignal > 1)
  {
    for (int i = 0; i < 1; i++)
    {
      digitalWrite(LEDPins[i], HIGH);
    }
    for (int i = 1; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(LEDPins[i], LOW);
    }
  }
}

