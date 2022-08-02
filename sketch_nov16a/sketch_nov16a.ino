void setup()
{
  pinMode(13,OUTPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);
}
void loop()
{
  if (digitalRead(6)== LOW)
  {
    digitalWrite(13,HIGH);
    
    delay(10);
  }
  else 
  {
    
    digitalWrite(13,LOW);
    delay(10);
    
  }
  
}
