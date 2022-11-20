void setup() {
  // initialize digital pin 13 as an output.
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  while (digitalRead(12) == HIGH) {}
  digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for half a second
  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  delay(500);              // wait for half a second
}