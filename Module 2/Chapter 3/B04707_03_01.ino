int IRTransmitter = 8;
int IRReceiver = A0; //IR Receiver is connected to pin 5

int buzzer = 9; // Buzzer is connected with pin 9.
int output = 0; // Variable to store the value from the IR sensor
int ambientLight = 500;

void setup()
{
  pinMode(IRReceiver, INPUT);
  pinMode(IRTransmitter, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(IRTransmitter, HIGH);
}
void loop()
{
  output = analogRead(IRReceiver);
  // If anything comes in between the IR Transmitter and IR receiver
  // IR receiver will not give the output. Make an alarm.
  if (output < ambientLight)
  {
    makeAlarm(50);
  }
}
void makeAlarm(unsigned char time)
{
  analogWrite(buzzer, 170);
  delay(time);
  analogWrite(buzzer, 0);
  delay(time);
}

