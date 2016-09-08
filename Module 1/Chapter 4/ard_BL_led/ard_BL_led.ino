char bluetoothVal;           //value sent over via bluetooth
char lastValue;              //stores last state of device (on/off)
 
int ledPin = 13;

void setup() {
 Serial.begin(9600); // begin communication on baud 9600
 pinMode(ledPin, OUTPUT); // set the led pin to output
}
 
 
void loop() {
  if(Serial.available()) // searches for available data
  {//if there is data being recieved
    bluetoothVal=Serial.read(); //read it
  }
  if (bluetoothVal=='1')
  {//if value from bluetooth serial is '1'
    digitalWrite(ledPin,HIGH);     // turn on LED
    if (lastValue!='1')
      Serial.println(F("LED ON")); //print LED is on
    lastValue = bluetoothVal;
  }
  else if (bluetoothVal=='0')
  {//if value from bluetooth serial is '0'
    digitalWrite(ledPin,LOW);       //turn off LED
    if (lastValue!='0')
      Serial.println(F("LED OFF")); //print LED is off
    lastValue = bluetoothVal;
  }
  delay(1000);
}
