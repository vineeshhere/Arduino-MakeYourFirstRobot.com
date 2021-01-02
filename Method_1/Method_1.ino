int trigger = 4;
int echopin = 5; 
int Motor1 = 9;
int Motor2 = 10;

int duration;
int distance;
void setup() {
    pinMode(Motor1, OUTPUT);
     pinMode(Motor2, OUTPUT);
/* When the Arduino writes HIGH to trigger pin, sonar
will generate ultra- sound. Hence trigger pin has to
configure for OUTPUT */
pinMode(trigger, OUTPUT);
/* echo pin of the sonar will go high when it receives
the transmitted sound from the sonar. So echo pin has
to be read for knowing the pin status. So echo pin has to
be configured for INPUT */
pinMode(echopin, INPUT);
digitalWrite(trigger, LOW); 
Serial.begin(9600); 
/*configure the serial monitor for
printing the distance. */
}
void loop() {
delay(500);
 /* Keeping some delay before starts
transmitting the sound. */
/* Following code will produce ultrasound for 10
microseconds by providing HIGH
pulse for 10 microseconds */
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);
/* PulseIn returns the length of the pulse in echo pin.
It reads the state of the echo pin. Here it waits for the
echo pin state to go from LOW to HIGH.*/
duration = pulseIn(echopin, HIGH);
distance = duration * 0.0340/2; 
Serial.print("Distance:");

Serial.println(distance); 
if (distance <= 100) {
  digitalWrite(Motor1, HIGH);
     digitalWrite(Motor2, LOW);
     delay(500); //wait for robot to make a right turn.
} else {
digitalWrite(Motor1, HIGH);
digitalWrite(Motor2, LOW);
} 
}

