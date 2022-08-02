int enA = 9;
int in1 = 8;
int in2 = 11;

int enB = 10;
int in3 = 12;
int in4 = 13;

void inits(){
  pinMode(2, INPUT); // declare A0 as input pin for left sensor
  pinMode(3, INPUT); // declare A1 as input pin for right sensor
  pinMode (enA , OUTPUT);
  pinMode (enB , OUTPUT);
  pinMode (in1 , OUTPUT);
  pinMode (in2 , OUTPUT);
  pinMode (in3 , OUTPUT);
  pinMode (in4 , OUTPUT);
}

void setup() {
  inits();
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Line Follower Rover");
  delay(500);

  //analogWrite(enA, 200);
  //analogWrite(enB, 200);
}

//Follows a line with 2 sensors detecting if it is under a white or black surface.
void lineFollower(){
  int leftSensor = digitalRead(3);
  int rightSensor = digitalRead(2);

  Serial.print(rightSensor);
  Serial.print("  ");
  Serial.print(leftSensor);
  delay(100);

  if ((rightSensor == 1) && (leftSensor == 1))
  {
    analogWrite(enA, 200);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, 200);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  //Turn left if left sensor (sensor 1) detects black line
  else if ((rightSensor == 0) && (leftSensor == 1))
    //motor1 is left motor, motor 2 is right motor
  {
    analogWrite(enA, 200);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, 50);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
   //Turn right if right sensor detects black line
  else if ((rightSensor == 1) && (leftSensor == 0))
    //motor1 is left motor, motor 2 is right motor
  {
    analogWrite(enA, 50);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, 200);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void demo(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);

  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(3000);

}

void loop() {
  lineFollower();
  
  
}
