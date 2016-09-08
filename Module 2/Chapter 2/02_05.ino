int LDR = 0; //will be getting input from pin A0
int LDRValue = 0;
int light_sensitivity = 400;    //This is the approx value of light surrounding your LDR
int LED = 13;

void setup()
{
  Serial.begin(9600);          //start the serial monitor with 9600 buad
  pinMode(LED, OUTPUT);
  
}
 
void loop()
{
  LDRValue = analogRead(LDR);     //Read the LDR’s value through LDR pin A0 
  Serial.println(LDRValue);       //Print the LDR values to serial monitor
  
  if (LDRValue < light_sensitivity) 
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  delay(50);        //Delay before LDR value is read again
}

