int motorPos = 3;
int motorNeg = 4;

void setup() {
  pinMode(motorPos, OUTPUT);
  pinMode(motorNeg, OUTPUT);
}

void loop() {
  //run the motor in one direction
  digitalWrite(motorPos, HIGH);
  digitalWrite(motorNeg, LOW);
  delay(5000); //Run for 5 seconds
  // Reverse the direction of the motor
  digitalWrite(motorPos, LOW);
  digitalWrite(motorNeg, HIGH);
  delay(5000);
}

