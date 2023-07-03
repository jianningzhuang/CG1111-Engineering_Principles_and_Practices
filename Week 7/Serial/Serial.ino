


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  Serial.println("Hi");
  delay(1000);

}
