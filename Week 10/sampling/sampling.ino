
#define AWG 0 //INPUT at A0

int period = 20; //change for each sampling rate

void setup() {
  Serial.begin(9600); //begin serial communication
  for (int i = 0; i < 50; i++){
    int val = analogRead(AWG);
    Serial.print(millis());
    Serial.print(",");
    Serial.println(val);
    delay(period);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
