 /* Complete program for reference */
#include <Servo.h>

#define LEFT_TURN 120
#define RIGHT_TURN 60
#define KEEP_STRAIGHT 90
#define COLLISION_POINT 20

#define ACTUATOR_PIN 3
#define TRIGGER 4 
#define ECHO_PIN 5
#define REVERSE_MOTOR_PIN1 6
#define REVERSE_MOTOR_PIN2 7
#define MOTOR_PIN1  9
#define MOTOR_PIN2  10

Servo sonar_actuator;
  int uturn=0;
  long duration; int distance;
void robotStop() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
}
void TurnRobotRight() { 
  digitalWrite(MOTOR_PIN1,HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  delay(1000);
}
void TurnRobotleft() { 
  digitalWrite(MOTOR_PIN1,LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  delay(1000);
}

void MoveRobotForward() {
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, HIGH);
}
void makeUturn() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  delay(1000);
}

void TakeReverse() {
  digitalWrite(REVERSE_MOTOR_PIN1, HIGH);
  digitalWrite(REVERSE_MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  delay(3000);
  digitalWrite(REVERSE_MOTOR_PIN1, LOW);
  digitalWrite(REVERSE_MOTOR_PIN2, LOW);
}

int measureDistance() {
  int temp;
  delay(500); /*Keeping some delay before it starts
transmitting the sound.*/ /* Following code will
produce ultrasound for 10us(microseconds) by
providing HIGH pulse for 10 microseconds */
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
/* PulseIn returns the length of the pulse in echo pin.
It reads the state of the echo pin. Here it waits for the
echo pin state to go from HIGH to LOW. */
  duration = pulseIn(ECHO_PIN, HIGH);
  temp = duration * 0.0340/2; /* distance = (time taken
X speed of the sound)/2. */
  Serial.print("Distance:");
  Serial.println(temp);
  return temp;
}
void setup() { delay(5000);
/* When the Arduino write HIGH to TRIGGER pin, sonar
will generate ultrasound. Hence the TRIGGER pin has to
configure for OUTPUT */
  pinMode(TRIGGER, OUTPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(REVERSE_MOTOR_PIN1, OUTPUT);
  pinMode(REVERSE_MOTOR_PIN2, OUTPUT);
  sonar_actuator.attach(ACTUATOR_PIN);
  sonar_actuator.write(KEEP_STRAIGHT);
/* echo pin of the sonar will go high when it receives
the transmitted sound from the sonar. So the echo
pin has to be read for knowing the pin status. So the
ECHO_PIN has to be configured for INPUT */
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIGGER, LOW);
  Serial.begin(9600); /* configure the serial monitor
printing the distance. */
  sonar_actuator.write(LEFT_TURN);
  delay(1000);
  sonar_actuator.write(RIGHT_TURN); 
  delay(3000);
}
void loop() {
  distance = measureDistance();
  if (distance < COLLISION_POINT) {
    robotStop();
    sonar_actuator.write(LEFT_TURN); 
    distance = measureDistance();
    if (distance > COLLISION_POINT) {
      TurnRobotleft();
    } else {
       sonar_actuator.write(RIGHT_TURN); 
       distance = measureDistance();
       if (distance > COLLISION_POINT)
          TurnRobotRight();
       else {
          uturn++;
          if(uturn > 1) {
            TakeReverse();
            uturn = 0;
          }else
            makeUturn();
       }
    }
  } else { 
       MoveRobotForward();
  }
  sonar_actuator.write(KEEP_STRAIGHT);
}
