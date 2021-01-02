#include <Servo.h>

Servo RotorServo;
Servo ArmHeight;
Servo ArmClaw;
Servo ArmUpdwn;
int RotorServoPin = 5;
int ArmHeightPin = 6;
int ArmHUpdwnPin = 3;
int Armclawpin = 9;

#define RTR_START_POS  30
#define ARM_HEIGHT_POS  50
#define ARM_UPDWN_POS  40
#define ARM_CLAW_OPEN  70
#define ARM_CLAW_CLOSE  10

void moveArmSlowly(Servo temp, int curpos, int target_angle) {
  int i;
  if ((target_angle - curpos) > 0) {
    for(i = curpos;i <= target_angle; i++) {
      temp.write(i);
      delay(100);
    }
  } else {
     for(i = curpos;i >= target_angle; i--) {
      temp.write(i);
      delay(100);
    }
    
  }
  
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
RotorServo.attach(RotorServoPin);
ArmHeight.attach(ArmHeightPin);
ArmUpdwn.attach(ArmHUpdwnPin);
ArmClaw.attach(Armclawpin);

RotorServo.write(RTR_START_POS);
ArmHeight.write(ARM_HEIGHT_POS);
ArmUpdwn.write(ARM_UPDWN_POS);
ArmClaw.write(ARM_CLAW_OPEN);
delay(3000);
ArmClaw.write(ARM_CLAW_CLOSE);

delay(10000);
}





void moveleft_do_action() {

RotorServo.write(0);

ArmHeight.write(60);
ArmUpdwn.write(40);
delay(2000);
ArmHeight.write(90);
delay(2000);
ArmUpdwn.write(10);
delay(2000);
//ArmHeight.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("start position");
moveArmSlowly(ArmUpdwn, 40, 20);
moveArmSlowly(ArmHeight, 50, 90);
delay(1000);
moveArmSlowly(ArmUpdwn, 20, 10);
moveArmSlowly(ArmUpdwn, 10, 20);
moveArmSlowly(ArmHeight, 90, 50);
moveArmSlowly(ArmUpdwn, 20, 40);
delay(2000);
//moveArmSlowly(&ArmUpdwn, 40, 10);
moveArmSlowly(RotorServo, 30, 110);

delay(2000);
Serial.println("second position");
moveArmSlowly(ArmUpdwn, 40, 90);
moveArmSlowly(ArmHeight, 50, 80);
delay(10000);
moveArmSlowly(ArmUpdwn, 90, 40);
delay(1000);
moveArmSlowly(ArmHeight, 80, 50);
delay(1000);
moveArmSlowly(RotorServo, 110, 30);
//moveleft_do_action();
//moveArmSlowly(&RotorServo, 45, 0);
delay(5000);

}
