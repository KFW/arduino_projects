// VR3_claw_trial
// get Vex Claw arm working with Seeed Studio Motor Shield

/*******************
uses Seeed Studio motor shield

code based on examples from:
http://www.seeedstudio.com/wiki/Motor_Shield_V1.0

*******************/

#include <Servo.h>
Servo wrist;
Servo claw;



void setup() {
  wrist.attach(6);
  claw.attach(7);  
}

void loop() {
  int test = 0;
  if (test == 0);{
    delay(1000);
    wrist.write(0); // should be forward down position
    delay(500);  
    claw.write(10); // since pads in place don't close fully
    delay(500);
    wrist.write(90); // upright; overshoots @ 127
    delay(500);
    claw.write(65);  // open 1/4 to release
    
    
    test = 1;
  } // end if 
}   // end loop


