#define RED_LED 11 // PWM fähiger PIN
void setup()
{
  pinMode(RED_LED, OUTPUT);
}
void loop()
{
  for (int i = 0; i < 255; i++)
  {
    analogWrite(RED_LED, i); // Den Wert i setzen
    delay(10);
  }
  for (int i = 255; i > 0; i--)
  {
    analogWrite(RED_LED, i); // Den Wert i setzen
    delay(10);
  }
}
