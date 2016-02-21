     
unsigned long wristsig; // elevator
unsigned long clawsig;  // aileron


void setup() {

  pinMode(14, INPUT); // A0; for wrist
  pinMode(15, INPUT); // A1; for claw


  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  wristsig = pulseIn(14, HIGH, 25000); // Read the pulse width of wrist signal
  clawsig = pulseIn(15, HIGH, 25000); 


  Serial.print("W: ");
  Serial.print(wristsig);
  Serial.print("\t  C: ");
  Serial.println(clawsig);

  delay(100); // I put this here just to make the terminal window happier
}
