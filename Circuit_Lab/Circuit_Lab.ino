int trigPin = 12;
int echoPin = 11;

float duration_us, distance_cm;
void setup() {
  // put your setup code here, to run once:
  // begin serial communication with 9600 baudrate speed
  Serial.begin (9600);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // generate 10-microsecond pulse to TRIG 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // measure duration of pulse from ECHO 
  duration_us = pulseIn(echoPin, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  // Speed of sound wave, 0.034m/us divided by 2
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(500);

}
