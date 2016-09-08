#include <IRremote.h>
const int IR_RECEIVER = 11;
IRrecv receiver(IR_RECEIVER);
decode_results buttonPressed;
long int buttonValue = 0;
const long int buttonOne = 54528; //Update value one according to your readings
const long int buttonTwo = 54572; //Update value two according to your readings

int LEDpin = 9;

void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn(); // Start the receiver
  pinMode(LEDpin, OUTPUT);
}

void loop()
{
  if (receiver.decode(&buttonPressed))
  {
    buttonValue = buttonPressed.value;
    Serial.println(buttonValue);
    switch (buttonValue) {
      case buttonOne:
        digitalWrite(LEDpin, HIGH);
        break;
      case buttonTwo:
        digitalWrite(LEDpin, LOW);
        break;
      default:
        Serial.println("Waiting for input. ");
    }
    receiver.resume(); // Receive the next value
  }
  delay(100);
}

