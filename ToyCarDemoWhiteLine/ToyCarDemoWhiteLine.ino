#include <IRremote.h> // Library for IR receiver
#define irPin 4 // Pin for IR receiver

IRrecv irrecv(irPin); //receives the input from controller
decode_results rslts; // stores them in rslts

// Initializes pins for each motor
int enA = 5; 
int in1 = 8;
int in2 = 11;

int enB = 6;
int in3 = 12;
int in4 = 13;

int speed = 200;


void inits(){
  pinMode(2, INPUT); // declare pin 2 as input pin for left sensor
  pinMode(3, INPUT); // declare pin 3 as input pin for right sensor
  pinMode (enA , OUTPUT); //declares enA as output for motor
  pinMode (enB , OUTPUT); //declares enB as output for motor
  pinMode (in1 , OUTPUT); //declares in1 as output for motor
  pinMode (in2 , OUTPUT); //declares in2 as output for motor
  pinMode (in3 , OUTPUT); //declares in3 as output for motor
  pinMode (in4 , OUTPUT); //declares in4 as output for motor
}

void setup() {
  inits(); //calls for the inits function above
  Serial.begin(19200); // set up Serial library at 19200 bps
  irrecv.enableIRIn(); // enables the IR input
  Serial.println("Line Follower Rover"); // Just to see Serial Monitor
  delay(500);
  TCCR0B = TCCR1B & B11111000 | B00000010;
}
 //Follows a line with 2 sensors detecting if it is under a white or black surface.
void lineFollower(){
  int leftSensor = digitalRead(3); //initializes pin for left sensor
  int rightSensor = digitalRead(2); //initializes pin for right sensor

  // Serial Monitor
  Serial.print(rightSensor);
  Serial.print("  ");
  Serial.print(leftSensor);
  delay(100);

  // Go forward if both sensors detect black line
  if ((rightSensor == 1) && (leftSensor == 1))
  {
    Forward();
    delay(50);
  }
  //Turn right if left sensor detects black line
  else if ((rightSensor == 1) && (leftSensor == 0))
    //motor1 is left motor, motor 2 is right motor
  {
    Right();
    delay(50);
  }
   //Turn left if right sensor detects black line
  else if ((rightSensor == 0) && (leftSensor == 1))
    //motor1 is left motor, motor 2 is right motor
  {
    Left();
    delay(50);
  }
  //Stop if both sensors 
  else if ((rightSensor == 0) && (leftSensor == 0))
  {
    Stop();
    delay(50);
  }
}

void IRController(){

  if (irrecv.decode(&rslts)) { //if the IR reciever outputs a number
      Serial.println(rslts.value); // prints the number in the serial monitor
      
      switch (rslts.value) {
        
         case 16718055:            //  FORWARD Button
            Forward();
            Serial.println("FORWARD");
            break;
 
         case 16716015:            //  LEFT Button
            Left();
            Serial.println("LEFT");
            break;   
 
         case 16734885:            //  RIGHT Button
            Right();
            Serial.println("RIGHT");
            break;
 
         case 16730805:            //  BACK Button
            Reverse();
            Serial.println("REVERSE");
            break;
        
         case 16726215:            //  STOP Button
            Stop();
            Serial.println("STOP");
            break;
            
         case 16738455:            //  LINE FOLLOWING Button
            lineFollower();
            Serial.print("LINE FOLLOWER");
            break;

         case 16756815:            //  BACK TO IR CONTROLLER Button
            IRController();
            Serial.println("IR CONTROLLER");
            break;
   }      
   irrecv.resume();
   } 
}

//Function to go forward
void Forward(){
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

//Function to turn right
void Right(){
    analogWrite(enA, speed);//speed of motor A
    digitalWrite(in1, HIGH); //Motor spins forward
    digitalWrite(in2, LOW);
    analogWrite(enB, 0);//speed of motor B
    digitalWrite(in3, HIGH); //Motor spins forward
    digitalWrite(in4, LOW);
}
//Function to turn left
void Left(){
    analogWrite(enA, 0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enB, speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
 //Function to go reverse
void Reverse(){
    analogWrite(enA, speed);
    digitalWrite(in1, LOW);//Motor spins backwards
    digitalWrite(in2, HIGH);
    analogWrite(enB, speed);
    digitalWrite(in3, LOW);//Motor spins backwards
    digitalWrite(in4, HIGH);
}
//function to stop
void Stop(){
    digitalWrite(in1, LOW); //Turns off motor
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}



void loop() {
  //IRController();
  lineFollower();
}
