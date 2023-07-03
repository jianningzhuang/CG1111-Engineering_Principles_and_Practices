//LED brightness gradually increases from 0 to 255 then 0 abruptly

void setup() {
  pinMode(11, OUTPUT);

}

void loop() {
  for (int i = 0; i < 256; i++){
    analogWrite(11, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i-= 5){
    analogWrite(11, i);
    delay(10);
  }

}
