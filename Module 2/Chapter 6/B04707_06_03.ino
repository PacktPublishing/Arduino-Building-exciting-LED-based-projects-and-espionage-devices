int leftMotorPos = 10;
int leftMotorNeg = 9;
int rightMotorPos = 12;
int rightMotorNeg = 13;

void setup()
{
  pinMode(leftMotorPos, OUTPUT);
  pinMode(rightMotorPos, OUTPUT);
  pinMode(leftMotorNeg, OUTPUT);
  pinMode(rightMotorNeg, OUTPUT);
}

void loop()
{
  forward();
  delay(5000);
  right();
  delay(5000);
  left();
  delay(5000);
  reverse();
  delay(5000);
  stopAll();
  delay(5000);
}

void forward() {
  digitalWrite(rightMotorPos, HIGH);
  digitalWrite(leftMotorPos, HIGH);
  digitalWrite(rightMotorNeg, LOW);
  digitalWrite(leftMotorNeg, LOW);
}

void left() {
  digitalWrite(rightMotorPos, HIGH);
  digitalWrite(leftMotorPos, LOW);
  digitalWrite(rightMotorNeg, LOW);
  digitalWrite(leftMotorNeg, LOW);
}

void right() {
  digitalWrite(rightMotorPos, LOW);
  digitalWrite(leftMotorPos, HIGH);
  digitalWrite(rightMotorNeg, LOW);
  digitalWrite(leftMotorNeg, LOW);
}

void reverse() {
  digitalWrite(rightMotorPos, LOW);
  digitalWrite(leftMotorPos, LOW);
  digitalWrite(rightMotorNeg, HIGH);
  digitalWrite(leftMotorNeg, HIGH);
}

void stopAll() {
  digitalWrite(rightMotorNeg, LOW);
  digitalWrite(leftMotorNeg, LOW);
  digitalWrite(rightMotorPos, LOW);
  digitalWrite(leftMotorPos, LOW);
}

