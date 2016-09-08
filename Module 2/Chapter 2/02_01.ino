// Initializing LEDs for using it in the code.
// Initializing outside any function so global variable can be accessed throughout the code

int redLed = 9;
int yellowLed = 10;
int greenLed = 11;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin for red, yellow and green led as an output.
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(redLed, HIGH);       //    Making red led high
  digitalWrite(yellowLed, LOW);     //    Making yellow led low
  digitalWrite(greenLed, LOW);      //    Making green led low
  delay(10000);                     //    Wait for 10 seconds (10000 milliseconds)
  digitalWrite(redLed, LOW);        //    Making red led low
  digitalWrite(yellowLed, LOW);     //    Making yellow led low
  digitalWrite(greenLed, HIGH);     //    Making green led high
  delay(10000);                     //    Wait for 10 seconds (10000 milliseconds)
  digitalWrite(redLed, LOW);        //    Making red led low
  digitalWrite(yellowLed, HIGH);    //    Making yellow led high
  digitalWrite(greenLed, LOW);      //    Making green led low
  delay(3000);                      //    Wait for 3 seconds 3000 milliseconds)
}

