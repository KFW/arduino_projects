     
#include <Servo.h> 

Servo servo1;
int ch1max = 1680;    // pulse width for ch1 full forward (plus a bit more for wiggle room)
int ch1min = 920;     // full back (minus a bit for wiggle room)
int servo1max = 180;  // max angle for servo
int servo1min = 0;    // min angle for servo
int servoangle;       // initialize servo angle

unsigned long ch1; // Here's where we'll keep our channel values

void setup() {

  pinMode(5, INPUT); // Set our input pins as such
  servo1.attach(9); 

}

void loop() {

  ch1 = pulseIn(5, HIGH, 25000); // Read the pulse width of RC signal
  servoangle = map(ch1, ch1min, ch1max, servo1min, servo1max);
  
  servo1.write(servoangle);
  
  delay(100); // to give things a chance to catch up

}
