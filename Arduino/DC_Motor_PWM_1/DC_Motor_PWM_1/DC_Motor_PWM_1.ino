int MOTORPIN = 3;

void setup()
{
  pinMode(MOTORPIN, OUTPUT);
}

void loop()
{
  digitalWrite(MOTORPIN, HIGH);
  delay(2000);
  digitalWrite(MOTORPIN, LOW);
  delay(2000);
}
