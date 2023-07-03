
//if variable resistor is higher, blink faster and vice versa

void setup() {
  pinMode(11, OUTPUT);

}

void loop() {
  int delayVal;
  int resist = analogRead(A0);
  if (resist > 512){
    delayVal = 50;
  }
  else{
    delayVal = 1000;
  }
  digitalWrite(11, HIGH);
  delay(delayVal);
  digitalWrite(11, LOW);
  delay(delayVal);

}
