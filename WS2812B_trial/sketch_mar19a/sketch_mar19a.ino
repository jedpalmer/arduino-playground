void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0, HIGH);
  delay(1500);
  digitalWrite(0, LOW);
  delay(1500);
}
