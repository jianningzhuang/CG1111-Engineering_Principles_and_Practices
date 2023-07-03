

//void setup() {
//  pinMode(6, OUTPUT);
//  pinMode(9, OUTPUT);
//  pinMode(10, OUTPUT);
//  pinMode(11, OUTPUT);
//
//}

//Activity 1

//void loop() {
//  digitalWrite(6, HIGH);
//  delay(200);
//  digitalWrite(6, LOW);
//  delay(200);
//  digitalWrite(9, HIGH);
//  delay(200);
//  digitalWrite(9, LOW);
//  delay(200);
//  digitalWrite(10, HIGH);
//  delay(200);
//  digitalWrite(10, LOW);
//  delay(200);
//  digitalWrite(11, HIGH);
//  delay(200);
//  digitalWrite(11, LOW);
//  delay(200);
//}

//Activity 2

//void loop(){
//  for (int i = 0; i <= 255; i++){
//    analogWrite(6, i);
//    delay(2);
//  }
//  for (int i = 255; i >= 0; i--){
//    analogWrite(6, i);
//    delay(2);
//  }
//  for (int i = 0; i <= 255; i++){
//    analogWrite(9, i);
//    delay(2);
//  }
//  for (int i = 255; i >= 0; i--){
//    analogWrite(9, i);
//    delay(2);
//  }
//  for (int i = 0; i <= 255; i++){
//    analogWrite(10, i);
//    delay(2);
//  }
//  for (int i = 255; i >= 0; i--){
//    analogWrite(10, i);
//    delay(2);
//  }
//  for (int i = 0; i <= 255; i++){
//    analogWrite(11, i);
//    delay(2);
//  }
//  for (int i = 255; i >= 0; i--){
//    analogWrite(11, i);
//    delay(2);
//  }
//}

//ACtivity 3

//void setup(){
//  Serial.begin(9600);
//  
//}

//void loop(){
//  if (Serial.available() > 0){
//    char data = Serial.read();
//    Serial.write(data+1);
//  }
//}


//Activity 4

void setup(){
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  if (Serial.available() > 0){
    char data = Serial.read();
    if (data == '1'){
      digitalWrite(6, HIGH);
      delay(200);
      digitalWrite(6, LOW);
      delay(200);
      digitalWrite(9, HIGH);
      delay(200);
      digitalWrite(9, LOW);
      delay(200);
      digitalWrite(10, HIGH);
      delay(200);
      digitalWrite(10, LOW);
      delay(200);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
      delay(200);
    }
    else if (data == '2'){
      for (int i = 0; i <= 255; i++){
        analogWrite(6, i);
        delay(2);
      }
      for (int i = 255; i >= 0; i--){
        analogWrite(6, i);
        delay(2);
      }
      for (int i = 0; i <= 255; i++){
        analogWrite(9, i);
        delay(2);
      }
      for (int i = 255; i >= 0; i--){
        analogWrite(9, i);
        delay(2);
      }
      for (int i = 0; i <= 255; i++){
        analogWrite(10, i);
        delay(2);
      }
      for (int i = 255; i >= 0; i--){
        analogWrite(10, i);
        delay(2);
      }
      for (int i = 0; i <= 255; i++){
        analogWrite(11, i);
        delay(2);
      }
      for (int i = 255; i >= 0; i--){
        analogWrite(11, i);
        delay(2);
      }
    }
  }
}
