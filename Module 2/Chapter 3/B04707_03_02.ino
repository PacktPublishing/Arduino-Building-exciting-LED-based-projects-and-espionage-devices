#include <IRremote.h>
const int IR_RECEIVER = 11;
IRrecv receiver(IR_RECEIVER);
decode_results buttonPressed;
void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn(); // Start the receiver
}

void loop()
{
  if (receiver.decode(&buttonPressed))
  {
    Serial.println(buttonPressed.value); //Printing values coming from the IR Remote
    receiver.resume(); // Receive the next value
  }
  delay(100);
}

