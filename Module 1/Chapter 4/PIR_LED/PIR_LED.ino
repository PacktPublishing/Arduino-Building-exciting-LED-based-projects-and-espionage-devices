int ledPin = 13; // use the onboard LED
int pirPin = 2; // 'out' of PIR connected to digital pin 2
int pirState = LOW; // start the state of the PIR to be low (no motion)
int pirValue = 0; // variable to store change in PIR value

void setup() {
  pinMode(ledPin, OUTPUT); // declare the LED as output
  pinMode(pirPin, INPUT);  // declare the PIR as input
  Serial.begin(9600); // begin the Serial port at baud 9600
}

void loop() {
  pirValue = digitalRead(pirPin); // read PIR value
  if ((pirValue == HIGH)&&(pirState==LOW)) { // check if motion has occured 
    digitalWrite(ledPin, HIGH); // turn on LED
    Serial.println("Motion detected!");
    pirState = HIGH; // set the PIR state to ON/HIGH
    delay(1000); // wait for a second
  }
  else { // if there is no motion
    digitalWrite(ledPin, LOW); // turn off LED
    if(pirState == HIGH) {
    // prints only if motion has happened in the first place
    Serial.println("No more motion!\n");
    pirState = LOW; // sets the PIR state to OFF/LOW
    delay(200); // small delay before proceeding
    }
  }    
}
