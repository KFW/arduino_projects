/* RC_AFmotorshield_claw_test
control SparkFun robot arm (https://www.sparkfun.com/products/11524 & https://www.sparkfun.com/products/11674)
with
Adafruit motor shield (https://learn.adafruit.com/adafruit-motor-shield/overview)
*/

#include <Servo.h> 

Servo wrist;
Servo claw;

// constants for handling RC signal inputs
const int RCwrist = 14; // pin A0 on AF motor shield; get signal from elevator control
const int RCclaw = 15;  // pin A1 on AF motor shield; get signal from aileron control

const unsigned long RCsigMax = 1890;      // pulse width for max signal from Turnigy 5x (plus a bit more for wiggle room)
const unsigned long RCsigMin = 1030;       // full back (minus a bit for wiggle room)
const unsigned long RCsigMidHigh = 1480;  // for setting dead zone in middle
const unsigned long RCsigMidLow = 1450;

// constants for constraining servo range of movement
const int MinWristAngle = 0; 
const int MaxWristAngle = 180;
const int MinClawAngle = 35;
const int MaxClawAngle = 155;
const int DeltaMin = 2; // use for adjusting claw responsiveness
const int DeltaMax = 20;

// variables 
int wristangle;
int clawangle;
int angledelta;
unsigned long wristsig;
unsigned long clawsig;

void setup() {

  pinMode(RCwrist, INPUT); // Set our input pins as such
  pinMode(RCclaw, INPUT);
  wrist.attach(9); // AF motor shield Servo2
  claw.attach(10); // AF motor shield Servo1

  // initialize servos at midpoints
  wristangle = (MinWristAngle + MaxWristAngle)/2;
  clawangle = (MinClawAngle + MaxClawAngle)/2;
  wrist.write(wristangle);
  claw.write(clawangle);

  delay(1000);
    
//  Serial.begin(9600); // for print debugging
  
}

void loop() {

  wristsig = pulseIn(RCwrist, HIGH, 25000); // Read the pulse width of wrist signal
  clawsig = pulseIn(RCclaw, HIGH, 25000); 
  
  
  if (wristsig > RCsigMidHigh) {
    // adjust amount wrist changes proportionate to joystick travel
    angledelta =  map(wristsig, RCsigMidHigh, RCsigMax, DeltaMin, DeltaMax);
    wristangle = wristangle + angledelta;
  }
  else if (wristsig < RCsigMidLow) {
    angledelta = map(wristsig, RCsigMin, RCsigMidLow, DeltaMax, DeltaMin);
    wristangle = wristangle - angledelta;
  }

  
  if (clawsig > RCsigMidHigh) {
    // adjust amount claw changes proportionate to joystick travel
    angledelta =  map(clawsig, RCsigMidHigh, RCsigMax, DeltaMin, DeltaMax);
    clawangle = clawangle + angledelta;
  }
  else if (clawsig < RCsigMidLow) {
    angledelta = map(clawsig, RCsigMin, RCsigMidLow, DeltaMax, DeltaMin);
    clawangle = clawangle - angledelta;
  }
  
  wristangle = constrain(wristangle, MinWristAngle, MaxWristAngle);
  clawangle = constrain(clawangle, MinClawAngle, MaxClawAngle);
  
  wrist.write(wristangle);
  claw.write(clawangle);
  
//  // for debugging  
//  Serial.print("W: ");
//  Serial.print(wristsig);
//  Serial.print(" (");
//  Serial.print(wristangle);
//  Serial.print(") \t  C: ");
//  Serial.print(clawsig);
//  Serial.print(" (");
//  Serial.print(clawangle);
//  Serial.println(")");
  
  delay(50); // to give things a chance to catch up

}
