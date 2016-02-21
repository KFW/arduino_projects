/* RC_CustomProtoShield_claw_test
control SparkFun robot arm (https://www.sparkfun.com/products/11524 & https://www.sparkfun.com/products/11674)
with
Custom Arduino protshield to drive servos 
Power directly from batteries with upgraded 7.2V servo motors - only commands from Arduino
*/

#include <Servo.h> 

Servo wrist;
Servo claw;

// constants for handling RC signal inputs
const int RCwrist = 14; // pin A0 on AF motor shield; get signal from elevator control
const int RCclaw = 15;  // pin A1 on AF motor shield; get signal from aileron control

// constants for constraining servo range of movement
const int MinWristAngle = 0; 
const int MaxWristAngle = 180;
const int MinClawAngle = 35;
const int MaxClawAngle = 155;
const int DeltaMin = 2; // use for adjusting claw responsiveness
const int DeltaMax = 10;

// variables 
int wristangle;
int clawangle;
int angledelta;


void setup() {

  pinMode(RCwrist, INPUT); // Set our input pins as such
  pinMode(RCclaw, INPUT);
  wrist.attach(12);  
  claw.attach(13); 

  // initialize servos at minima
  wristangle = MinWristAngle;
  clawangle = MinClawAngle;
  wrist.write(wristangle);
  claw.write(clawangle);

  delay(1000);
    
//  Serial.begin(9600); // for print debugging
  
} // end setup()

void loop() {
  // open claw
  while (clawangle < MaxClawAngle) {
    claw.write(clawangle);
    clawangle++;
    delay(20);  
  } 
  //close claw
  while (clawangle > MinClawAngle) {
    claw.write(clawangle);
    clawangle--;
    delay(20);
  }
  delay(1000);
  // raise wrist
  while (wristangle < MaxWristAngle) {
    wrist.write(wristangle);
    wristangle++;
    delay(20);  
  } 
  //close claw
  while (wristangle > MinWristAngle) {
    wrist.write(wristangle);
    wristangle--;
    delay(20);
  }
  
  delay(2000);

} // end loop()
