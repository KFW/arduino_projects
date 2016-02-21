// robot_claw_AF_servo_test
// control SparkFun robot arm (https://www.sparkfun.com/products/11524 & https://www.sparkfun.com/products/11674)
// Adafruit motor shield (https://learn.adafruit.com/adafruit-motor-shield/overview)
// using buttons

#include <Servo.h>
Servo wrist; 
Servo claw;

const int Blue = 14;   // A0 - these are pins exposed on AF motor shield
const int Yellow = 15; // A1
const int Green = 16;  // A2
const int Red = 17;    // A3
// constants for constraining servo range of movement
const int MinWristAngle = 0; 
const int MaxWristAngle = 180;
const int MinClawAngle = 25;
const int MaxClawAngle = 155;

int wristAngle;
int clawAngle;
int reading = 0; // for holding values temporarily


void setup() {
  Serial.begin(9600);
  wrist.attach(9); // servo2 on AF motor shield
  claw.attach(10); // servo1 on AF motor shield
  pinMode(Blue, INPUT_PULLUP); // so I can use buttons to pull-down
  pinMode(Yellow, INPUT_PULLUP);  
  pinMode(Green, INPUT_PULLUP);
  pinMode(Red, INPUT_PULLUP);
  wristAngle = 90; // put wrist in upright position
  clawAngle = 45;  // put claw partly open
  
  delay(500); // let electronics settle
  wrist.write(wristAngle); 
  claw.write(clawAngle);  
} // end setup()

void loop() {
  // read through buttons
  reading = digitalRead(Blue);
  if (reading == LOW){
    wristAngle++;
  }
  reading = digitalRead(Yellow);
  if (reading == LOW){
    wristAngle--;
  }
  reading = digitalRead(Green);
  if (reading == LOW){
    clawAngle++;
  }
  reading = digitalRead(Red);
  if (reading == LOW){
    clawAngle--;
  }
   
  // ensure angles don't go out of range
  wristAngle = constrain(wristAngle, MinWristAngle, MaxWristAngle);
  clawAngle = constrain(clawAngle, MinClawAngle, MaxClawAngle);
  
  // write angles to servos
  wrist.write(wristAngle);
  claw.write(clawAngle);
  
  delay(10); // allow time for movement
  
//  // so I can see what limits I might need to enforce on range of travel
//  Serial.print("Wrist: ");
//  Serial.print(wristAngle); 
//  Serial.print("\t");
//  Serial.print("Claw:");
//  Serial.println(clawAngle);
} // end loop()
