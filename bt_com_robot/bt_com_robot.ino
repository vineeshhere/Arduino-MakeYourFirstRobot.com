
#include <Servo.h>

#define BT_PWR  2
#define REVERSE_PIN1 6
#define REVERSE_PIN2 7
#define MOTOR_PIN1 9
#define MOTOR_PIN2 10
#define LEFT_TURN 120
#define RIGHT_TURN 60
#define KEEP_STRAIGHT 90
#define COLLISION_POINT 20
#define TRIGGER 4 
#define ECHO_PIN 5
#define ACTUATOR_PIN 3

Servo sonar_actuator;
long duration; 
int distance;

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
delay(1000);
}

void TakeReverse() {
digitalWrite(REVERSE_PIN1, HIGH);
digitalWrite(REVERSE_PIN2, HIGH);
digitalWrite(MOTOR_PIN1, LOW);
digitalWrite(MOTOR_PIN2, LOW);
delay(1000);
digitalWrite(REVERSE_PIN1, LOW);
digitalWrite(REVERSE_PIN2, LOW);
}
void showFaceExpressionNo() {

   sonar_actuator.write(LEFT_TURN); 
   sonar_actuator.write(RIGHT_TURN); 
   sonar_actuator.write(LEFT_TURN); 
   sonar_actuator.write(KEEP_STRAIGHT); 
   
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
char data=0;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(BT_PWR, OUTPUT);
   digitalWrite(BT_PWR, HIGH);
   pinMode(MOTOR_PIN1, OUTPUT);
pinMode(MOTOR_PIN2, OUTPUT);
pinMode(REVERSE_PIN1, OUTPUT);
pinMode(REVERSE_PIN2, OUTPUT);
sonar_actuator.attach(ACTUATOR_PIN);
pinMode(TRIGGER, OUTPUT);
pinMode(ECHO_PIN, INPUT);
digitalWrite(TRIGGER, LOW);  

}

void loop() {
  // put your main code here, to run repeatedly:
   if(Serial.available() > 0) {
    data = Serial.read();
    Serial.println(data);
    if( data == '1' && measureDistance > COLLISION_POINT)
      MoveRobotForward();
    else if(measureDistance <= COLLISION_POINT)
      showFaceExpressionNo();

    if( data == '2')
      TurnRobotleft();
    if( data == '3')
      TurnRobotRight();
     if( data == '4')
       TakeReverse(); 
    
   
   }
    
    
      robotStop();
   
   

}

